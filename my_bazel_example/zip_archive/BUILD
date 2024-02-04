load("//zip_archive:rule.bzl", "zip_archive")

zip_archive(
    name = "zip_archive",
    source_files = ["Readme.md", "main"],
    output = "app.zip"
)

# 使用bazel提供的现有API来执行压缩
# bazel build //zip_archive:zip_archive_genrule
genrule(
    name = "zip_archive_genrule",
    srcs = [
        "Readme.md",
        "main"
    ],
    outs = ["release.zip"],

    # 注意这里对参数取值用大写
    cmd = "zip $(OUTS) $(SRCS)"
)