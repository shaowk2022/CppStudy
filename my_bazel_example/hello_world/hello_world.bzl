def generate_file_impl(ctx):
    print("=== Target {}===".format(ctx.label))
    
    # 将ctx中的output_file取出来给new_file
    new_file = ctx.actions.declare_file(ctx.attr.output_file)
    print(new_file)

    # 定义一个行为：内容来自于text属性，输出到new_file
    ctx.actions.write(
        content = ctx.attr.text,
        output = new_file
    )
    return DefaultInfo(
        files = depset([new_file])
    )

generate_file = rule(
    implementation = generate_file_impl,
    attrs = {
        "text": attr.string(mandatory = True),
        "output_file": attr.string(mandatory = True)
    }
)