set(module_name "runtime")

file(GLOB_RECURSE torchlight_${module_name}_files ${torchlight_src_dir}/${module_name}/*.cpp)
set(torchlight_backend_files ${torchlight_backend_files} ${torchlight_${module_name}_files})