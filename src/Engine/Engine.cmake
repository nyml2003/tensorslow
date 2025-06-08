set(module_name "Engine")

file(GLOB_RECURSE tensorslow_${module_name}_files ${tensorslow_src_dir}/${module_name}/*.cpp)
set(tensorslow_Compiler_files ${tensorslow_Compiler_files} ${tensorslow_${module_name}_files})