load("//printer:printer.bzl", "printer", "printer_with_label")
# // 代表bazel项目根路径, "printer"代表printer.bzl里面的函数名

# load("@src//printer:printer.bzl", "printer")
# 添加@src表示//printer:printer.bzl所在的项目

# 这个printer和load的第二个参数对应，name的值随意
printer(
    name = "printer",
    number = 2,
) 

# ":printer"代表第二个参数是引用printer标签，也就是上面这个
# 在 Bazel 中，标签以冒号开头，用于引用同一包或目录中的目标。
printer_with_label(
    name = "printer_with_label",
    mylabel = ":printer",
)