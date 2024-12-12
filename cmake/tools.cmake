add_custom_target(
    LOC
    COMMAND find
    ${torchlight_src_dir}
    -type f -name "*.h" -o -name "*.cpp"
    | xargs wc -l
    COMMENT "Counting lines of code"
)
