 auto it = categories.find(extension);
    if (it != categories.end()) {
        return it->second;
    }