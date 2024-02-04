def impl_zip_archive(ctx):
    # 通过output形参取出输出文件名称
    out_file = ctx.outputs.output
    # zip xxx.zip source_file1 source_file2 ...

    # 获取args参数并附加上输出文件名和源文件列表
    args = ctx.actions.args()
    args.add(out_file)
    args.add_all(ctx.files.source_files)
    
    # 运行zip命令
    ctx.actions.run(
        executable = "zip",
        arguments = [args],
        inputs = ctx.files.source_files,
        outputs = [out_file]
    )
    return DefaultInfo(
        files = depset([out_file])
    )


zip_archive = rule(
    implementation = impl_zip_archive,
    attrs = {
        # 源文件列表，输出文件
        "source_files": attr.label_list(allow_files = True),
        "output": attr.output(mandatory = True),

    }
)