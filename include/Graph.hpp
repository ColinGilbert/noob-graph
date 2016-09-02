// Near minimal as graphs get.
#pragma once

#include <cstdint>
#include <limits>
#include <assert.h>

#include <algorithm>
#include <vector>

#include "Component.hpp"

namespace noob
{

	typedef noob::handle<uint32_t> node_handle;
	class graph
	{
		public:



		bool path_exists(noob::node_handle first, noob::node_handle second) const noexcept(true)
		{
			if (!is_valid(first) || !is_valid(second)) return false;

			return (std::find(nodes[first.index()].outgoing.begin(), nodes[first.index()].outgoing.end(), second.index()) != nodes[first.index()].outgoing.end());		
		}

		uint32_t num_nodes() const noexcept(true)
		{
			return nodes.size();
		}

		void add_path(noob::node_handle first, noob::node_handle second) noexcept(true)
		{
			if (is_valid(first) && is_valid(second))
			{
				// Don't wanna add no duplicates
				if (std::find(nodes[first.index()].outgoing.begin(), nodes[first.index()].outgoing.end(), second.index()) == nodes[first.index()].outgoing.end())
				{
					nodes[first.index()].outgoing.push_back(second.index());
				}
			}
		}

		noob::node_handle add_node() noexcept(true)
		{
			noob::graph::node n;
			nodes.push_back(n);
			return noob::node_handle::make(nodes.size() - 1);
		}

		bool is_valid(noob::node_handle n) const noexcept(true)
		{
			if (!(n.index() < nodes.size()))
			{
				return false;
			}
			return nodes[n.index()].valid;
		}

		void set_valid(noob::node_handle n, bool b) noexcept(true)
		{
			if (n.index() < nodes.size())
			{
				nodes[n.index()].valid = b;
			}
		}

		protected:

		struct node
		{
			node() noexcept(true) : valid(true) {}

			// static constexpr uint32_t invalid = std::numeric_limits<uint32_t>::max();

			bool valid;
			std::vector<uint32_t> outgoing;
		};

		std::vector<noob::graph::node> nodes;
	};
}
