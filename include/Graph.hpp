// Near minimal as graphs get.
#pragma once

#include <cstdint>
#include <limits>
#include <assert.h>

#include <rdestl/vector.h>
#include <rdestl/list.h>



namespace noob
{

	struct graph
	{
		struct node
		{
			node() noexcept(true) : valid(true) {}

			static constexpr uint32_t invalid = std::numeric_limits<uint32_t>::max();

			bool valid;
			rde::vector<uint32_t> outgoing;
		};

		// Member functions
		bool node_valid(uint32_t n) const
		{
			if (n > nodes.size() - 1)
			{
				return false;
			}
			return nodes[n].valid;
		}

		rde::vector<node> nodes;
	};
}
