def impl(ctx):
    print("hello")
    print("Target: {}, attr.number: {}".format(ctx.label, ctx.attr.number))

#dir()打印变量的成员

printer = rule(
    # implementation = impl表示将rule的实现对应到函数impl
    implementation = impl,
    # attrs指定属性，名称number, 类型为int，默认值为1
    attrs = {
        "number": attr.int(default = 1)
    },
)

# 流程: BUILD文件负责模块的调用，然后.bzl文件里面定义函数头(这里的printer=rule(), 里面传入函数的rule的实现，形参)
#       def用来定义rule的真正实现对应的函数，即这里的impl

def impl_with_label(ctx):
    print(ctx.attr.mylabel)

printer_with_label = rule(
    implementation = impl_with_label,
    attrs = {
        "mylabel": attr.label(),
    }
)