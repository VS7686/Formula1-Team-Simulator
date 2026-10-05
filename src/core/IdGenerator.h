#pragma once

namespace f1 {

// Hands out unique integer ids (static member shared by all objects).
class IdGenerator {
public:
    static int next() { return ++s_counter; }

private:
    static inline int s_counter = 0;
};

}  // namespace f1
