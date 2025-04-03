set(module_name "Compiler")

file(GLOB_RECURSE torchlight_${module_name}_files ${torchlight_src_dir}/${module_name}/*.cpp)
set(torchlight_Compiler_files ${torchlight_Compiler_files} ${torchlight_${module_name}_files})