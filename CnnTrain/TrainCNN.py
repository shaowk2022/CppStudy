import onnx
import torch
import torch.nn as nn
import torch.optim as optim
from torch.utils.data import DataLoader, Dataset
from torchvision import transforms, datasets
import os
from PIL import Image

# 定义 CNN 模型
class CNNModel(nn.Module):
    def __init__(self, num_classes):
        super(CNNModel, self).__init__()
        self.conv1 = nn.Conv2d(3, 32, kernel_size=3, stride=1, padding=1)
        self.relu1 = nn.ReLU()
        self.pool1 = nn.MaxPool2d(kernel_size=2, stride=2)

        self.conv2 = nn.Conv2d(32, 64, kernel_size=3, stride=1, padding=1)
        self.relu2 = nn.ReLU()
        self.pool2 = nn.MaxPool2d(kernel_size=2, stride=2)

        self.conv3 = nn.Conv2d(64, 128, kernel_size=3, stride=1, padding=1)
        self.relu3 = nn.ReLU()
        self.pool3 = nn.MaxPool2d(kernel_size=2, stride=2)

        self.fc1 = nn.Linear(128 * 8 * 8, 512)
        self.relu4 = nn.ReLU()
        self.dropout = nn.Dropout(0.5)  # 添加 Dropout
        self.fc2 = nn.Linear(512, num_classes)

    def forward(self, x):
        x = self.pool1(self.relu1(self.conv1(x)))
        x = self.pool2(self.relu2(self.conv2(x)))
        x = self.pool3(self.relu3(self.conv3(x)))
        x = x.view(x.size(0), -1)
        x = self.relu4(self.fc1(x))
        x = self.dropout(x)  # 添加 Dropout
        x = self.fc2(x)
        return x

# 自定义数据集类
class LicensePlateDataset(Dataset):
    def __init__(self, data_dir, transform=None):
        self.data_dir = data_dir
        self.transform = transform
        self.classes = os.listdir(data_dir)
        self.image_paths = []
        self.labels = []

        for idx, class_name in enumerate(self.classes):
            class_dir = os.path.join(data_dir, class_name)
            for img_name in os.listdir(class_dir):
                self.image_paths.append(os.path.join(class_dir, img_name))
                self.labels.append(idx)

    def __len__(self):
        return len(self.image_paths)

    def __getitem__(self, idx):
        img_path = self.image_paths[idx]
        image = Image.open(img_path).convert('RGB')
        label = self.labels[idx]

        if self.transform:
            image = self.transform(image)

        return image, label

# 数据预处理
transform = transforms.Compose([
    transforms.Resize((64, 64)),
    transforms.RandomHorizontalFlip(),  # 随机水平翻转
    transforms.RandomRotation(10),     # 随机旋转
    transforms.ColorJitter(brightness=0.2, contrast=0.2, saturation=0.2),  # 颜色抖动
    transforms.ToTensor(),
    transforms.Normalize(mean=[0.485, 0.456, 0.406], std=[0.229, 0.224, 0.225])  # ImageNet 标准化
])

# 加载数据集
train_dataset = LicensePlateDataset(data_dir='dataset/train', transform=transform)
val_dataset = LicensePlateDataset(data_dir='dataset/val', transform=transform)

train_loader = DataLoader(train_dataset, batch_size=32, shuffle=True)
val_loader = DataLoader(val_dataset, batch_size=32, shuffle=False)

# 初始化模型、损失函数和优化器
num_classes = len(train_dataset.classes)
model = CNNModel(num_classes=num_classes)
criterion = nn.CrossEntropyLoss()
optimizer = optim.Adam(model.parameters(), lr=0.001)

# 训练函数
def train(model, train_loader, criterion, optimizer, device):
    model.train()
    running_loss = 0.0
    correct = 0
    total = 0

    for images, labels in train_loader:
        images, labels = images.to(device), labels.to(device)

        optimizer.zero_grad()
        outputs = model(images)
        loss = criterion(outputs, labels)
        loss.backward()
        optimizer.step()

        running_loss += loss.item()
        _, predicted = outputs.max(1)
        total += labels.size(0)
        correct += predicted.eq(labels).sum().item()

    train_loss = running_loss / len(train_loader)
    train_acc = 100.0 * correct / total
    return train_loss, train_acc

# 验证函数
def validate(model, val_loader, criterion, device):
    model.eval()
    running_loss = 0.0
    correct = 0
    total = 0

    with torch.no_grad():
        for images, labels in val_loader:
            images, labels = images.to(device), labels.to(device)

            outputs = model(images)
            loss = criterion(outputs, labels)

            running_loss += loss.item()
            _, predicted = outputs.max(1)
            total += labels.size(0)
            correct += predicted.eq(labels).sum().item()

    val_loss = running_loss / len(val_loader)
    val_acc = 100.0 * correct / total
    return val_loss, val_acc

# # 训练和验证
# device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
# model = model.to(device)
# num_epochs = 30
# scheduler = torch.optim.lr_scheduler.StepLR(optimizer, step_size=5, gamma=0.1)  # 每 5 轮学习率乘以 0.1
# for epoch in range(num_epochs):
#     train_loss, train_acc = train(model, train_loader, criterion, optimizer, device)
#     val_loss, val_acc = validate(model, val_loader, criterion, device)
#     scheduler.step()  # 更新学习率

#     print(f'Epoch [{epoch+1}/{num_epochs}], '
#           f'Train Loss: {train_loss:.4f}, Train Acc: {train_acc:.2f}%, '
#           f'Val Loss: {val_loss:.4f}, Val Acc: {val_acc:.2f}%')
# # 保存模型
# torch.save(model.state_dict(), 'license_plate_cnn.pth')
# print("Model saved as license_plate_cnn.pth")

# pth转为ONNX格式
# 假设你已经定义并训练好了 CNNModel
model = CNNModel(num_classes=num_classes)
model.load_state_dict(torch.load('license_plate_cnn.pth'))  # 加载训练好的权重
model.eval()  # 将模型设置为评估模式

# 创建一个示例输入张量（与模型输入大小一致）
# 假设输入图像大小为 64x64，通道数为 3
dummy_input = torch.randn(1, 3, 64, 64)  # 批次大小为 1

# 导出模型为 ONNX 格式
onnx_path = 'license_plate_cnn.onnx'
torch.onnx.export(
    model,                  # 要导出的模型
    dummy_input,            # 示例输入
    onnx_path,              # 导出的 ONNX 文件路径
    input_names=['input'],  # 输入节点名称
    output_names=['output'],  # 输出节点名称
    # dynamic_axes={'input': {0: 'batch_size'}, 'output': {0: 'batch_size'}},  # 支持动态批次大小
    verbose=True
)

print(f"Model exported to {onnx_path}")