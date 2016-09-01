// Near minimal as graphs get.
#pragma once

#include <cstdint>
#include <limits>
#include <assert.h>

#include <rdestl/vector.h>


#include "Component.hpp"

namespace noob
{

	class graph
	{
		typedef noob::component::handle<noob::graph::node> node_handle;

		bool path_exists(uint32_t)

		noob::graph::node_handle node_add()
		{
			noob::graph::node n;
			return nodes.add(n);
		}

		// Member functions
		bool node_valid(noob::graph::node_handle n) const
		{
			if (nodes.exists(n)
			{
				return false;
			}
			return nodes.get_unsafe(n).valid;
		}

	protected:

		struct node
		{
			node() noexcept(true) : valid(true) {}

			static constexpr uint32_t invalid = std::numeric_limits<uint32_t>::max();

			bool valid;
			rde::vector<uint32_t> outgoing;
		};


		noob::component<noob::graph::node> nodes;
	};
}
