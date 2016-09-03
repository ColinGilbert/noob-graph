// Near minimal as naive_graphs get.
#pragma once

#include <cstdint>
#include <limits>
#include <assert.h>

#include <algorithm>
#include <vector>

#include "Component.hpp"
#include "MathFuncs.hpp"

#include <rdestl/sort.h>

namespace noob
{
	typedef noob::handle<uint32_t> node_handle;

	class flat_graph
	{
		public:
			// Does not affect the graph. Therefore if you have a constant graph, you can iterate over it from anywhere.
			// However, you MUST use has_next() - which is extremely cheap - prior to calling get_next() or else you'll either get garbage or a segfault.
			class visitor
			{
				friend class flat_graph;
				public:

					bool has_next() const noexcept(true)
					{
						return valid;
					}
					
					noob::node_handle get_next() noexcept(true)
					{
						++child_counter;
						current_edge = g.edges[first_pos + child_counter];
						valid = is_valid();
					}

					void reset() noexcept(true)
					{
						child_counter = 0;
						valid = is_valid();
					}

				protected:

					visitor(const noob::flat_graph& graph_arg, const noob::node_handle n) noexcept(true)
					{
						g = graph_arg;
						child_counter = 0;
						n_children = g.num_children(n);
						const std::tuple<uint32_t, uint32_t> unpacked_node = noob::pack_64_to_32(g.nodes[n.index()]);
						first_pos = std::get<0>(unpacked_node);
						last_pos = std::get<0>(unpacked_node) + std::get<1>(unpacked_node);
						current_child = std::get<1>(g.edges[first_pos]);
						valid = is_valid();
					}

					bool is_valid() const noexcept(true)
					{
						return (first_pos + child_counter) < last_pos;
						
					}
					const noob::flat_graph& g;
					uint32_t child_counter
					const uint32_t first_pos, last_pos;
					uint32_t current_child;
					bool valid;
			};

			friend class visitor;

			flat_graph() noexcept(true) : num_nodes(0) {}

			uint32_t num_nodes() const noexcept(true)
			{
				return num_nodes;
			}

			noob::node_handle add_node() noexcept(true)
			{
				++ num_nodes;
				nodes.push_back(noob::pack_32_to_64(noob::flat_graph::invalid_32, 0));
				
				assert(num_nodes - 1 == nodes.size());
				return noob::handle::make(num_nodes - 1);
			}

			uint32_t num_children(const noob::node_handle n) const noexcept(true)
			{
				return std::get<1>(noob::pack_64_to_32(nodes[n.index()]));
			}

			// uint32_t get_children(const noob::node_handle n, rde::vector<noob::node_handle>& arg) const noexcept(true);

			bool is_child(const noob::node_handle first, const noob::node_handle second) const noexcept(true)
			{
				const std::tuple<uint32_t, uint32_t> parent_numchildren = noob::pack_64_to_32(nodes[first.index]);
				if (std::get<1>(parent_numchildren) > 0)
				{
					const uint32_t end_pos = std::get<0>(parent_numchildren) + std::get<1>(parent_numchildren);
					return (rde::lower_bound(noob;:pack32_to_64(first.index(), second.index()), &edges[std::get<0>(parent_numchildren)], &edges[end_pos]) != &edges[end_pos]);
				}

				return false;
			}

			void add_child(const noob::node_handle first, const noob::node_handle second) noexcept(true)
			{
				const uint64_t old = noob::pack_64_to_32(nodes[first.index()]);

				nodes[first.index()] = noob::pack_32_to_64(std::get<0>(old), std::get<1>(old) + 1);
				
				edges.push_back(noob::pack_32_to_64(std::get<0>(old), second.index()));

				valid = false;
			}

			bool node_valid(const noob::node_handle n) const noexcept(true)
			{
				return (n.index() < nodes.size());
			}

			bool graph_valid() const noexcept(true)
			{
				return valid;
			}

			noob::flat_graph::node_visitor get_visitor(const noob::node_handle n) const noexcept(true)
			{
				noob::flat_graph::node_visitor results(*this, n);
				return results;
			}

			void sort() noexcept(true)
			{
				rde::quick_sort(edges.begin(), edges.end());
			}

			void clear() noexcept(true)
			{
				edges.clear();
				nodes.clear();
				num_nodes = 0;
				valid = true;
			}

			void empty() noexcept(true)
			{
				edges.empty();
				nodes.empty();
				num_nodes = 0;
				valid = true;
			}

			void reserve(uin32_t num) noexcept(true)
			{
				edges.reserve(num);
				nodes.reserve(num);
			}


		protected:
			static constexpr uint32_t invalid_32 = std::numeric_limits<uint32_t>::max();
			static constexpr uint64_t invalid_64 = std::numeric_limits<uint64_t>::max();

			// The edges are stored as bitmasks.
			rde::vector<uint64_t> edges;
			// The node's bitmask: first 32 = first edge with node as parent, second 32 = num children.
			rde::vector<uint64_t> nodes;

			uint32_t num_nodes;

			bool valid;
	};





	class naive_graph
	{
		public:

			naive_graph() noexcept(true) : current_node(0), current_child(0) {}

			uint32_t num_nodes() const noexcept(true)
			{
				return nodes.size();
			}


			noob::node_handle add_node() noexcept(true)
			{
				noob::naive_graph::node n;
				nodes.push_back(n);
				return noob::node_handle::make(nodes.size() - 1);
			}

			rde::vector<noob::node_handle> get_children(const noob::node_handle n) const noexcept(true)
			{
				rde::vector<noob::node_handle> results;
				if (is_valid(n))
				{	
					const uint32_t num_children = nodes[n.index()].outgoing.size();
					for (uint32_t i = 0; i < num_children; ++i)
					{
						if (nodes[n.index()].valid == true)
						{
							results.push_back(noob::node_handle::make(nodes[n.index()].outgoing[i]));
						}
					}
				}
				return results;
			}

			uint32_t get_children(const noob::node_handle n, rde::vector<noob::node_handle>& arg) const noexcept(true)
			{
				const uint32_t num_to_search = nodes[n.index()].outgoing.size();
				uint32_t num_children = 0;
				arg.clear();
				for (uint32_t i = 0; i < num_to_search; ++i)
				{	
					if (nodes[nodes[n.index()].outgoing[i]].valid)
					{
						arg.push_back(noob::node_handle::make(i));
						++num_children;
					}
				}
				return num_children;
			}


			bool path_exists(const noob::node_handle first, const noob::node_handle second) const noexcept(true)
			{
				if (!is_valid(first) || !is_valid(second)) return false;

				return (std::find(nodes[first.index()].outgoing.begin(), nodes[first.index()].outgoing.end(), second.index()) != nodes[first.index()].outgoing.end());		
			}

			void add_path(const noob::node_handle first, const noob::node_handle second) noexcept(true)
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

			bool is_valid(const noob::node_handle n) const noexcept(true)
			{
				if (!(n.index() < nodes.size()) && n.index() != noob::naive_graph::node::invalid)
				{
					return false;
				}
				return nodes[n.index()].valid;
			}

			void set_valid(const noob::node_handle n, bool b) noexcept(true)
			{
				if (n.index() < nodes.size())
				{
					nodes[n.index()].valid = b;
				}
			}

			void empty() noexcept(true)
			{
				nodes.empty();
			}


		protected:

			struct node
			{
				node() noexcept(true) : valid(true) {}

				static constexpr uint32_t invalid = std::numeric_limits<uint32_t>::max();

				bool valid;
				std::vector<uint32_t> outgoing;
			};

			std::vector<noob::naive_graph::node> nodes;
	};


	typedef noob::naive_graph noob::graph;
}
