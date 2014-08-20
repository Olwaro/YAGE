#pragma once

#include <functional>
#include <boost/circular_buffer.hpp>

typedef std::function<void()> Action;
typedef boost::circular_buffer<Action*> ActionQueue;