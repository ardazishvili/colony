#pragma once

template <typename T, template <typename> class crtp_type>
struct crtp {
  T& wrapped() { return static_cast<T&>(*this); }
  const T& wrapped() const { return static_cast<const T&>(*this); }
};
