/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-arcade-lucas.mariette
** File description:
** dl
*/

#include "dl.hpp"

dl::dl(const std::string &path)
{
    std::ifstream test(path);
    if (!test.good()) {
        throw Error("File does not exist : " + path);
    }
    test.close();
    
    _path = path;
    _handle = dlopen(path.c_str(), RTLD_LAZY);
    if (!_handle) {
        throw Error(dlerror());
    }
}

dl::~dl()
{
    dlclose(_handle);
}

void *dl::getSym(const std::string &sym)
{
    void *ptr = dlsym(_handle, sym.c_str());
    if (!ptr) {
        throw Error(dlerror());
    }
    return ptr;
}

void *dl::getHandle() const
{
    return _handle;
}

void *dl::dlsym(void *handle, const char *symbol)
{
    return ::dlsym(handle, symbol);
}
