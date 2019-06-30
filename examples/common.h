#pragma once

#define CHECK(x) do { if (!(x)) { std::cout << "FAILED: " << #x << std::endl; std::abort(); } } while (false)
