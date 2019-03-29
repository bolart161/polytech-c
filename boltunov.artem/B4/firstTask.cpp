#include "tasks.hpp"
#include "PhoneBook.hpp"

typedef std::function<void(PhoneBook &, std::ostream &)> handler;

bool parseQuotedStr(std::string & str, std::istream & in)
{
  if (in.get() != '\"')
  {
    return false;
  }
  std::string buffer;
  do
  {
    std::getline(in, buffer, '\"');
    str += buffer;
    if (!buffer.empty() && buffer.back() == '\\')
    {
      str.pop_back();
      str.push_back('\"');
    }
  } while (!in.eof() && !buffer.empty() && str.back() == '\"');
  if (in.eof())
  {
    return false;
  }
  in.get();
  return true;
}

void parseError(PhoneBook &, std::ostream & out)
{
  out << "<INVALID COMMAND>" << std::endl;
}

handler parseAdd(std::istream & in)
{
  std::string strNumber;
  std::string strName;
  in >> std::ws;
  in >> std::ws >> strNumber >> std::ws;
  if (!parseQuotedStr(strName, in))
  {
    return parseError;
  }
  return handler([=](PhoneBook & editBook, std::ostream & out)
      {
        try
        {
          editBook.addRecord({strNumber, strName});
        }
        catch (std::invalid_argument &)
        {
          parseError(editBook, out);
        }
      });
}

handler parseStore(std::istream & in)
{
  std::string strMark;
  std::string strNewMark;
  in >> std::ws >> strMark;
  in >> std::ws >> strNewMark;
  return handler([=](PhoneBook & editBook, std::ostream & out)
      {
        try
        {
          editBook.setCurrentMark(strMark);
          editBook.duplicateMark(strNewMark);
        }
        catch (std::invalid_argument &)
        {
          parseError(editBook, out);
        }
      });
}

handler parseShow(std::istream & in)
{
  std::string strMark;
  in >> std::ws >> strMark;

  return handler([=](PhoneBook & editBook, std::ostream & out)
       {
        try
        {
          editBook.setCurrentMark(strMark);
        }
        catch (std::invalid_argument &)
        {
          out << "<INVALID BOOKMARK>" << std::endl;
          return;
        }
        if (editBook.empty())
        {
          out << "<EMPTY>" << std::endl;
          return;
        }
        PhoneBook::record_type record = editBook.getRecord();
        out << record.number << " " << record.name << std::endl;
      });
}

handler parseInsert(std::istream & in)
{
  std::string strLocation;
  std::string strMarkName;
  std::string strNumber;
  std::string strName;

  in >> std::ws >> strLocation;
  in >> std::ws >> strMarkName;
  in >> std::ws >> strNumber >> std::ws;
  if (!parseQuotedStr(strName, in))
  {
    return parseError;
  }

  if (strLocation == "before")
  {
    return handler([=](PhoneBook & editBook, std::ostream & out)
        {
          try
          {
            editBook.setCurrentMark(strMarkName);
            editBook.insertBefore({ strNumber, strName });
          }
          catch (std::invalid_argument &)
          {
            parseError(editBook, out);
          }
        });
  }
  else if (strLocation == "after")
  {
    return handler([=](PhoneBook & editBook, std::ostream & out)
        {
          try
          {
            editBook.setCurrentMark(strMarkName);
            editBook.insertAfter({ strNumber, strName });
          }
          catch (std::invalid_argument & ex)
          {
            parseError(editBook, out);
          }
        });
  }
  else
  {
    return parseError;
  }
}

handler parseDelete(std::istream & in)
{
  std::string strMark;
  in >> std::ws >> strMark;
  return handler([=](PhoneBook & editBook, std::ostream & out)
      {
        try
        {
          editBook.setCurrentMark(strMark);
          editBook.delRecord();
        }
        catch (std::invalid_argument &)
        {
          parseError(editBook, out);
        }
      });
}

handler parseMove(std::istream & in)
{
  std::string strMark;
  std::string strSteps;
  in >> std::ws >> strMark;
  in >> std::ws >> strSteps;
  if (strSteps == "first")
  {
    return handler([=](PhoneBook & editBook, std::ostream & out)
        {
          try
          {
            editBook.setCurrentMark(strMark);
            editBook.setMarkToFirst();
          }
          catch (std::invalid_argument &)
          {
            parseError(editBook, out);
          }
        });
  }
  else if (strSteps == "last")
  {
    return handler([=](PhoneBook & editBook, std::ostream & out)
        {
          try
          {
            editBook.setCurrentMark(strMark);
            editBook.setMarkToLast();
          }
          catch (std::invalid_argument &)
          {
            parseError(editBook, out);
          }
        });
  }
  int step = 0;
  try
  {
    step = std::stol(strSteps);
  }
  catch (std::invalid_argument &)
  {
    return handler([](PhoneBook &, std::ostream & out)
        {
          out << "<INVALID STEP>" << std::endl;
        });
  }
  return handler([=](PhoneBook & editBook, std::ostream & out)
      {
        try
        {
          editBook.setCurrentMark(strMark);
          editBook.moveMark(step);
        }
        catch (std::invalid_argument &)
        {
          parseError(editBook, out);
        }
      });
}
std::istream & operator >> (std::istream & in, handler & func)
{
  func = parseError;
  std::string line;
  getline(in, line);
  if (in.eof() && line.empty())
  {
    func = handler([](PhoneBook &, std::ostream &) {});
    return in;
  }
  std::istringstream istrIn(line);
  std::string comand;
  istrIn >> std::noskipws;
  istrIn >> comand;
  if (comand == "add")
  {
    func = parseAdd(istrIn);
  }
  else if (comand == "store")
  {
    func = parseStore(istrIn);
  }
  else if (comand == "show")
  {
    func = parseShow(istrIn);
  }
  else if (comand == "insert")
  {
    func = parseInsert(istrIn);
  }
  else if (comand == "delete")
  {
    func = parseDelete(istrIn);
  }
  else if (comand == "move")
  {
    func = parseMove(istrIn);
  }
  if (!istrIn.eof())
  {
    func = parseError;
  }

  return in;
}

void firstTask(std::istream & in, std::ostream & out)
{
  PhoneBook book;
  handler interpreter;

  while (!in.eof())
  {
    in >> interpreter;
    interpreter(book, out);
  }
}
