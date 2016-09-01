// Near minimal as graphs get.
#pragma once

#include <cstdint>
#include <limits>
#include <assert.h>

#include <rdestl/vector.h>
#include <rdestl/algorithm.h>

namespace noob
{
	class graph
	{
		bool path_exists(uint32_t first, uint32_t second) const noexcept(true)
		{
			if (!node_valid(first) || !node_valid(second)) return false;
			
			return (rde::find(nodes[first].outgoing.begin(), nodes[first].outgoing.end(), second) != nodes[first].outgoing.end());

			
		}

		uint32_t node_add() noexcept(true)
		{
			noob::graph::node n;
			return nodes.add(n);
		}

		// Member functions
		bool is_valid(uint32_t n) const noexcept(true)
		{
			if (!(n < nodes.size()))
			{
				return false;
			}
			return nodes[n].valid;
		}

		void set_valid(uint32_t n, bool b) noexcept(true)
		{
			if (n < nodes.size())
			{
				nodes[n].valid = b;
			}
		}

		protected:

		struct node
		{
			node() noexcept(true) : valid(true) {}

			static constexpr uint32_t invalid = std::numeric_limits<uint32_t>::max();

			bool valid;
			rde::vector<uint32_t> outgoing;
		};


		rde::vector<noob::graph::node> nodes;
	};
}
