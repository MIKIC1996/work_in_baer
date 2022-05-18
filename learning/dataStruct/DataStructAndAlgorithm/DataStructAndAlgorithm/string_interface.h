#pragma once

class string_interface
{
public:
	string_interface();
	~string_interface();

	virtual std::size_t size() = 0;
	virtual bool isEmpty() = 0;
	virtual void clear() = 0;
	virtual bool compare(string_interface const& tar) = 0;
	virtual void concat(string_interface const& tar) = 0;
	virtual bool subString(string_interface& dst , int start_pos,int size) = 0;
	virtual int indexOf(string_interface const& str,int start_pos) = 0;
	virtual void replace(string_interface const& src, string_interface const & dst) = 0;
	virtual void insertStr(string_interface const& tar, int insert_pos) = 0;
	virtual void deleteStr(int delete_pos , int size) = 0;
};

