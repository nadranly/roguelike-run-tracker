#ifndef SAVE_MANAGER_H
#define SAVE_MANAGER_H

#include <memory>
#include <string>
#include <vector>
#include "Character.h"

class SaveManager {
public:
    static void saveCharacters(const std::vector<std::unique_ptr<Character>>& characters,
                               const std::string& fileName);

    static std::vector<std::unique_ptr<Character>> loadCharacters(const std::string& fileName);
};

#endif
