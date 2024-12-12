set(module_name "generation")

file(GLOB_RECURSE torchlight_${module_name}_files ${torchlight_src_dir}/${module_name}/*.cpp)
set(torchlight_frontend_files ${torchlight_frontend_files} ${torchlight_${module_name}_files})