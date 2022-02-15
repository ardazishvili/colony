#pragma once

#include <ranges>

namespace ranges = std::ranges;

template <typename T>
void render(const T& container) {
  ranges::for_each(container, [](const auto& item) { item->render(); });
}

template <typename T>
void select(T&& container) {
  ranges::for_each(container, [](const auto& item) { item->select(); });
}

template <typename T>
void deselect(T&& container) {
  ranges::for_each(container, [](const auto& item) { item->deselect(); });
}
