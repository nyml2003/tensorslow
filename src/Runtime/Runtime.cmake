set(module_name "Runtime")

file(GLOB_RECURSE tensorslow_${module_name}_files ${tensorslow_src_dir}/${module_name}/*.cpp)
set(tensorslow_common_files ${tensorslow_common_files} ${tensorslow_${module_name}_files})