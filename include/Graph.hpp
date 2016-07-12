// Currently, this map lacks the ability to lookup parents. This may change. Also, the edges are stored as a hash-map, which takes up more memory than it otherwise could. Benchmark and fix?
#pragma once

#include <cstdint>
#include <limits>
#include <assert.h>

#include <rdestl/vector.h>
#include <rdestl/rdestl.h>
#include <rdestl/hash_map.h>
#include <rdestl/slist.h>


namespace noob
{
	template <typename T> class graph
	{
		protected:
			class node_it
			{
				friend class graph;

				void reset()
				{
					arc_index = 0;
				}

				bool has_next()
				{
					if (node_index < graph_ref.nodes.size())
				}

				protected:
					node_it(const graph& g, uint32_t n) noexcept(true) : graph_ref(g), node_index(n), arc_index(0) {}
					noob::graph& graph_ref;
					uint32_t node_index, arc_index;
			};



		protected:
			struct arc
			{
				arc() noexcept(true) : value(1), child(std::numeric_limits<uint32_t>::max()) {}
				uint32_t value, child;
			};

			struct node
			{
				node() noexcept(true) : valid(true) {}
				bool valid;
				rde::slist<arc> outgoing;

			};

			uint32_t n_edges, n_nodes;
			rde::vector<node> nodes;
			rde::vector<T> values;
	};
}
