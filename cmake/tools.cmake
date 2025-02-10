add_custom_target(
    LOC
    COMMAND find
    ${torchlight_src_dir}
    -path "${torchlight_src_dir}/MockFront" -prune -o \\\( -type f \\\( -name "*.h" -o -name "*.cpp" \\\) \\\) -print
    | xargs wc -l
    COMMENT "Counting lines of code"
)