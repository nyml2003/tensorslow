set(module_name "Object")

file(GLOB_RECURSE torchlight_${module_name}_files ${torchlight_src_dir}/${module_name}/*.cpp)
set(torchlight_common_files ${torchlight_common_files} ${torchlight_${module_name}_files})