#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;
template <typename type>
class Iterator
{
public:
	typedef typename vector<type>::iterator iter_type;
	Iterator(vector<type>& data) : m_data(data) {
		m_iter = m_data.begin();
		m_end = m_data.end();
	}
	void first() {
		m_iter = m_data.begin();
	}
	void next() {
		++m_iter;
	}
	bool isDone() const {
		return m_iter == m_end;
	}
	type current() const {
		return *m_iter;
	}
private:
	vector<type>& m_data;
	iter_type m_iter;
	iter_type m_end;
};

