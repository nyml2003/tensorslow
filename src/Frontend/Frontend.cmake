set(module_name "Frontend")

file(GLOB_RECURSE torchlight_${module_name}_files ${torchlight_src_dir}/${module_name}/*.cpp)
set(torchlight_frontend_entry_files ${torchlight_frontend_entry_files} ${torchlight_${module_name}_files})