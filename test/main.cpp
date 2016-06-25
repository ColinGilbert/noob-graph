#include <noob-graph/graph.hpp>
#include <iostream>
#include <sstream>
#include <string>


static const std::string n_of("number of");
static const std::string nodes_str("node");
static const std::string edges_str("edge");

static const std::string h_str("handle");
static const std::string expect_str("expected");
static const std::string got_str("got");

static unsigned int test_number = 0;

std::string space(const std::string& s)
{
}

std::string comma(const std::string& s)
{
}

std::string open_p(const std::string& s)
{
}

std::string close_p(const std::string& s)
{
}

std::string cap(const std::string& s)
{
}

std::string period(const std::string& s)
{
}

std::string colon(const std::string& s)
{
}

std::string semicolon(const std::string& s)
{
}

void log(const std::string& s)
{
	std::cout << s << std::endl;
}

void log_test(bool b, const std::string& test_name)
{
	std::stringstream ss;
	ss << test_number << ": " << test_name;
	if (b)
	{
		ss << ": PASS";
	}
	else
	{
		ss << ": FAIL";
	}
	log(ss.str());
	++test_number;
}

void test_node_add(noob::node_h expected_handle, uint32_t expected_num_nodes)
{
	
}

void test_edge_add(noob::node_h a, noob::node_h b, uint32_t expected_num_edges)
{

}

void test_node_del(noob::node_h n, uint32_t expected_num_nodes, uint32_t expected_num_edges)
{

}

void test_edge_del(noob::node_h a, noob::node_h b, uint32_t expected_num_edges)
{

}

int main()
{
	noob::dynamic_graph g;

	noob::node_h first_node = g.add_node();

	

	return 0;
}
