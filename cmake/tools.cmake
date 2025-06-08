add_custom_target(
        LOC
        COMMAND find
        ${tensorslow_src_dir}
        -path "${tensorslow_src_dir}/MockFront" -prune -o \\\( -type f \\\( -name "*.h" -o -name "*.cpp" \\\) \\\) -print
        | xargs wc -l
        COMMENT "Counting lines of code"
)