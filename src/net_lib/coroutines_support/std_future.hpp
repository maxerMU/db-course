#pragma once

#include <coroutine>

#include <future>

//////////////////////////////////////////////////////////////////////

template <typename T>
struct StdFutureCoroPromise {
  std::promise<T> promise_;

  auto get_return_object() {
    return promise_.get_future();
  }

  std::suspend_never initial_suspend() noexcept {
    return {};
  }

  std::suspend_never final_suspend() noexcept {
    return {};
  }

  void set_exception(std::exception_ptr e) {
    promise_.set_exception(std::move(e));
  }

  void unhandled_exception() {
    promise_.set_exception(std::current_exception());
  }

  template <typename U>
  void return_value(U &&u) {
    promise_.set_value(Ok(std::forward<U>(u)));
  }
};

template <typename R, typename... Args>
struct std::coroutine_traits<std::future<R>, Args...> {
using promise_type = StdFutureCoroPromise<R>;
};

//////////////////////////////////////////////////////////////////////

template <>
struct StdFutureCoroPromise<void> {
  std::promise<void> promise_;

  auto get_return_object() {
    return promise_.get_future();
  }

  std::suspend_never initial_suspend() noexcept {
    return {};
  }

  std::suspend_never final_suspend() noexcept {
    return {};
  }

  void set_exception(std::exception_ptr e) {
    promise_.set_exception(std::move(e));
  }

  void unhandled_exception() {
    promise_.set_exception(std::current_exception());
  }

  void return_void() {
    promise_.set_value();
  }
};

template <typename... Args>
struct std::coroutine_traits<std::future<void>, Args...> {
using promise_type = StdFutureCoroPromise<void>;
};
