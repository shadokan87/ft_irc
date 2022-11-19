/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu.escande@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 12:06:18 by matthieu          #+#    #+#             */
/*   Updated: 2022/04/04 12:06:43 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"
namespace parser
{

	bool	isInSet(char c, const std::string& set)
	{
		std::string::const_iterator beg = set.begin();
		std::string::const_iterator end = set.end();
		while (beg != end)
		{
			if (*beg == c)
				return (true);
			beg++;
		}
		return (false);
	}

	size_t countOccurence(std::string& line, const std::string& set)
	{
		std::string::const_iterator beg = line.begin();
		std::string::const_iterator end = line.end();
		size_t count = 0;
		while (beg != end)
		{
			if (isInSet(*beg, set))
				count++;
			beg++;
		}
		return (count);
	}
	inline bool	containOnlySet(std::string& current, const std::string& set)
	{
		return (countOccurence(current, set) == current.size() ? true : false);
	}
	std::vector<std::string> splitBySet(std::string& line, const std::string& set)
	{
		std::vector<std::string> ret;
		std::string current = "";
		std::string::const_iterator beg = line.begin();
		std::string::const_iterator end = line.end();
		bool set_ret = false;
		if (countOccurence(line, set) == 0)
		{
			ret.push_back(line);
			return (ret);
		}
		while (beg != end)
		{
			set_ret = isInSet(*beg, set);
			if (set_ret && !containOnlySet(current, set))
			{
				ret.push_back(current);
				current = "";
			}
			else if (!isInSet(*beg, set))
				current += *beg;
			beg++;
		}
		if (current != "")
			ret.push_back(current);
		return (ret);
	}
}
