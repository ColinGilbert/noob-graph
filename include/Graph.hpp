// Near minimal as graphs get.
#pragma once

#include <cstdint>
#include <limits>
#include <assert.h>

#include <rdestl/vector.h>



namespace noob
{

	class graph
	{
		
		uint32_t node_add()
		{
			noob::graph::node n;
			nodes.push_back(n);
			return nodes.size() - 1;
		}

		// Member functions
		bool node_valid(uint32_t n) const
		{
			if (n > nodes.size() - 1)
			{
				return false;
			}
			return nodes[n].valid;
		}

	protected:

		struct node
		{
			node() noexcept(true) : valid(true) {}

			static constexpr uint32_t invalid = std::numeric_limits<uint32_t>::max();

			bool valid;
			rde::vector<uint32_t> outgoing;
		};


		rde::vector<node> nodes;
	};
}
