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
	class graph
	{
		public:

			struct arc
			{
				arc() noexcept(true) : child(std::numeric_limits<uint32_t>::max()) {}
				uint32_t child;
			};

			struct node
			{
				node() noexcept(true) : valid(true) {}
				bool valid;
				rde::slist<arc> outgoing;

			};

			class node_it
			{
				friend class graph;

				public:

				void reset()
				{
					arc_index = 0;
				}

				bool has_next()
				{
					return (arc_index < (node_ref.outgoing.size() - 1));
				}
				
				void increment()
				{
					++arc_index;
				}

				uint32_t get_current_child()
				{
					return node_ref.outgoing[arc_index].child;
				}
				
				protected:
					node_it(noob::graph::node& n) noexcept(true) : node_ref(n), arc_index(0) {}
					noob::graph::node& node_ref;
					uint32_t arc_index;
			};


			// Member functions
			bool node_exists(uint32_t n) const
			{
				if (n > nodes.size() - 1)
				{
					return false;
				}
				return nodes[n].valid;
			}



		protected:

			uint32_t n_edges, n_nodes;
			rde::vector<node> nodes;
	};
}
