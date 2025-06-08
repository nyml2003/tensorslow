set(module_name "Frontend")

file(GLOB_RECURSE tensorslow_${module_name}_files ${tensorslow_src_dir}/${module_name}/*.cpp)
set(tensorslow_frontend_entry_files ${tensorslow_frontend_entry_files} ${tensorslow_${module_name}_files})