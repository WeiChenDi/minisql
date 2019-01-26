#include"Interpter.h"

int Interpreter::InterpreterFunc(API ap, string str)
{
	int posi = 0;
	string word = "";
	word = getWord(str, &posi);
	if (word == "create")//create 语句
	{
		word = getWord(str, &posi);
		//关于建表仅仅写了关于表的attribute和primarykey的建立，不能识别其他语句
		if (word == "table")//create table语句
		{
			int primary_Posi;
			word = getWord(str, &posi);//获得表名
			string primary_Key = "";
			string table_Name = "";
			if (word.empty() == 0)
			{
				table_Name = word;
			}
			else
			{
				cout << "Failure Message:: No table name" << endl;
				cout << endl;
				return 0;
			}
			word = getWord(str, &posi);
			if (word != "(")
			{
				cout << "Failure Message:: No attributes" << endl;
				cout << endl;
				return 0;
			}
			else//开始读取表内attribute名
			{
				//vector<PtrToAttribute>Attribute;
				string primaryKey = "";
				word = getWord(str, &posi);
				while (word != "primary"&&word != ")"&&word != "")
				{
					struct attribute tempAttribute;

					if (!word.empty())
					{
						tempAttribute.name = word;
					}
					else
					{
						cout << "Failure Message:: No getting the attribute name" << endl;
						cout << endl;
						return 0;
					}
					word = getWord(str, &posi);
					if (word == "int")
					{
						tempAttribute.type = INT;
					}
					else if (word == "float")
					{
						tempAttribute.type = FLOAT;
					}
					else if (word == "char")
					{
						word = getWord(str, &posi);
						if (word == "(")
						{
							word = getWord(str, &posi);
							if (!word.empty())
							{
								int charsize = stoi(word);
								tempAttribute.type = charsize;
								word = getWord(str, &posi);
								if (word != ")")
								{
									cout << "Failure Message:: Wrong format" << endl;
									cout << endl;
									return 0;
								}
							}
							else
							{
								cout << "Failure Message:: Failed to get char size" << endl;
								cout << endl;
								return 0;
							}
						}
						else
						{
							cout << "Failure Message:: Wrong start format" << endl;
							cout << endl;
							return 0;
						}
					}
					else
					{
						cout << "Failure Message:: Wrong type" << endl;
						cout << endl;
						return 0;
					}

					word = getWord(str, &posi);
					if (word == "," || word == ")")
					{
						//cout << tempAttribute.name << endl;
						attri.push_back(tempAttribute);
						if (word == ")")
						{
							break;
						}
						else
						{
							word = getWord(str, &posi);
							continue;
						}
					}
					else
					{
						if (word == "unique")
						{
							tempAttribute.ifUnique = 1;
							word = getWord(str, &posi);
							if (word == "," || word == ")")
							{
								attri.push_back(tempAttribute);
								if (word == ")")
								{
									break;
								}
								else
								{
									word = getWord(str, &posi);
									continue;
								}
							}
						}
						else
						{
							cout << "Failure Message:: Not in correct format" << endl;
							cout << endl;
							return 0;
						}

					}

				}
				//attribute读取完毕，可能遇到了primary key或直接结束
				if (word == "primary")
				{
					word = getWord(str, &posi);
					if (word == "key")
					{
						word = getWord(str, &posi);
						if (word == "(")
						{
							word = getWord(str, &posi);
							if (!word.empty())
							{
								primaryKey = word;
								int i;

								for (i = 0; i < (int)attri.size(); i++)
								{
									if (attri[i].name == primaryKey)
									{
										attri[i].ifPrimary = 1;
										primary_Posi = i;
										break;
									}
								}
								if (i == attri.size())
								{
									cout << "Failure Message:: Wrong primary key name" << endl;
									cout << endl;
									return 0;
								}
								word = getWord(str, &posi);
								if (word != ")")
								{
									cout << "Failure Message:: Wrong format" << endl;
									cout << endl;
									return 0;
								}
							}
							else
							{
								cout << "Failure Message:: Wrong format!" << endl;
								cout << endl;
								return 0;
							}
						}
						else
						{
							cout << "Failure Message::  ')' missing" << endl;
							cout << endl;
							return 0;
						}
					}
					else
					{
						cout << "Failure Message:: Didn't get right key word" << endl;
						cout << endl;
						return 0;
					}
				}
				word = getWord(str, &posi);
				if (word != ")")
				{
					cout << "Failure Message:: Wrong create table format" << endl;
					cout << endl;
					return 0;
				}
				else
				{
					word = getWord(str, &posi);
					if (word != ";")
					{
						cout << "Failure Message::Wrong create table format" << endl;
						cout << endl;
						return 0;
					}
				}
			}

			vector<Attribute> a;
			//CatalogManager catalog;

			for (int i = 0; i < attri.size(); i++)
			{
				if (attri[i].ifUnique == 1)
				{
					Attribute newAttri(attri[i].name, attri[i].type, true);
					a.push_back(newAttri);
				}
				else
				{
					Attribute newAttri(attri[i].name, attri[i].type, false);
					a.push_back(newAttri);
				}
			}
			attri.clear();
			Table newTable(table_Name, a, primary_Posi);
			ap.CreateTable(newTable);

			//catalog.CreateTable(newTable);

			//调用建表函数建立表格，可以传入表名、表的attribute向量，主键名称，可根据需要对以上内容进行修改
			return 1;
		}
		else if (word == "index")
		{
			char*  indexName = new char[100];
			char*  tableName = new char[100];
			char*  attriName = new char[100];
			word = getWord(str, &posi);
			if (word != "")
			{
				strcpy(indexName, word.c_str());
				word = getWord(str, &posi);
				if (word == "on")
				{
					word = getWord(str, &posi);
					if (word != "")
					{
						strcpy(tableName, word.c_str());
						word = getWord(str, &posi);
						if (word == "(")
						{
							word = getWord(str, &posi);
							if (word != "")
							{
								strcpy(attriName, word.c_str());
								word = getWord(str, &posi);
								if (word == ")")
								{
									word = getWord(str, &posi);
									if (word == ";")
									{
										ap.CreateIndex(indexName, tableName, attriName);
										delete indexName;
										delete tableName;
										delete attriName;
									}
									else
									{
										cout << "Failure Message:: Wrong format when create index" << endl;
										cout << endl;
										return 0;
									}
								}
								else
								{
									cout << "Failure Message:: Wrong format when create index" << endl;
									cout << endl;
									return 0;
								}
							}
							else
							{
								cout << "Failure Message:: Failed to get attri name" << endl;
								cout << endl;
								return 0;
							}
						}
						else
						{
							cout << "Failure Message:: Wrong format when create table" << endl;
							cout << endl;
							return 0;
						}
					}
					else
					{
						cout << "Failure Message:: Failed to get table name when create index" << endl;
						cout << endl;
						return 0;
					}
				}
				else
				{
					cout << "Failure Message:: Wrong format losing on when create index" << endl;
					cout << endl;
					return 0;
				}
			}
			else
			{
				cout << "Failure Message:: Failed to get index name" << endl;
				cout << endl;
				return 0;
			}
		}
		else
		{
			cout << "Failure Message:: Wrong create order" <<endl;
			cout << endl;
			return 0;
		}
	}
	//insert into Book values('001', 'DS', '15');
	else if (word == "insert")
	{
		string tableName = "";
		vector<string>recordContent;
		word = getWord(str, &posi);
		if (word == "into")
		{
			word = getWord(str, &posi);
			if (word != "")
			{
				tableName = word;
				word = getWord(str, &posi);
				if (word == "values")
				{
					word = getWord(str, &posi);
					if (word == "(")
					{
						word = getWord(str, &posi);
						while (word != "" && word != ")")
						{
							recordContent.push_back(word);
							word = getWord(str, &posi);
							if (word == ",")
							{
								word = getWord(str, &posi);
								continue;
							}
							else if (word == ")")
							{
								word = getWord(str, &posi);
								if (word == ";")
								{
									ap.InsertRecord(tableName, recordContent);
									return 1;
								}
								else
								{
									cout << "Failure Message:: Insert sentence wrong format" << endl;
									cout << endl;
									return 0;
								}
							}
							else
							{
								cout << "Failure Message:: Insert sentence wrong format when getting values" << endl;
								cout << endl;
								return 0;
							}
						}
					}
					else
					{
						cout << "Failure Message:: Insert sentence wrong format when getting values" << endl;
						cout << endl;
						return 0;
					}
				}
				else
				{
					cout << "Failure Message:: Insert sentence wrong format after table name" << endl;
					cout << endl;
					return 0;
				}
			}
			else
			{
				cout << "Failure Message:: Fail to get table name when inserting" << endl;
				cout << endl;
				return 0;
			}
		}
		else
		{
			cout << "Failure Message:: Insert sentence wrnog format" << endl;
			cout << endl;
			return 0;
		}
		

		return 1;
	}
	//select * from Book
	//select * from Book where BookNo = 'J0001'
	//select BookName from Book where BookNo = 'J0001'
	else if (word == "select")//选择操作
	{
		vector<string>selectAttribute;
		vector<Condition> conditionVec;
		string selectTableName = "";
		word = getWord(str, &posi);
		if (word == "*")
		{
			word = getWord(str, &posi);
			if (word == "from")
			{
				word = getWord(str, &posi);
				if (!word.empty())
				{
					selectTableName = word;
					word = getWord(str, &posi);
					if (word == "where")
					{
						string attriName = "";
						string value = "";
						int operation;
						while (word != ";")
						{
							word = getWord(str, &posi);		//列名
							attriName = word;
							word = getWord(str, &posi);		//conditoin
							if (word == "=")
							{
								operation = Condition::OPERATOR_EQUAL;
							}
							else if (word == "<>")
							{
								operation = Condition::OPERATOR_NOT_EQUAL;
							}
							else if (word == ">")
							{
								operation = Condition::OPERATOR_MORE;
							}
							else if (word == "<")
							{
								operation = Condition::OPERATOR_LESS;
							}
							else if (word == ">=")
							{
								operation = Condition::OPERATOR_MORE_EQUAL;
							}
							else if (word == "<=")
							{
								operation = Condition::OPERATOR_LESS_EQUAL;
							}
							else
							{
								cout << "Failure Message:: Wrong condition input" << endl;
								cout << endl;
								return 0;
							}
							word = getWord(str, &posi);
							if (word != "")
							{
								value = word;
							}
							else
							{
								cout << "Failure Message:: Wrong condition input" << endl;
								cout << endl;
								return 0;
							}
							Condition tmpCondition(attriName, value, operation);
							conditionVec.push_back(tmpCondition);
							word = getWord(str, &posi);
							if (word != "and" &&word != ";")
							{
								cout << "Failure Message:: Wrong select condition format" << endl;
								cout << endl;
								return 0;
							}

						}
						ap.RecordAllShow(selectTableName, conditionVec);
					}
					else
					{
						ap.RecordAllShow(selectTableName, conditionVec);
					}
				}
			}
			else
			{
				cout << "Failure Message:: No attribute name" << endl;
				cout << endl;
				return 0;
			}
		}
		else
		{
			cout << "Failure Message:: Wrong select format" << endl;
			cout << endl;
			return 0;
		}
		return 1;
	}
	else if (word == "drop")
	{
		string dropTableName = "";
		word = getWord(str, &posi);
		if (word == "table")
		{
			word = getWord(str, &posi);
			if (word != "")
			{
				dropTableName = word;
				ap.tableDrop(dropTableName);
				word = getWord(str, &posi);
				if (word == "")
				{
					cout << "Failure Message:: Wrong drop table format" << endl;
					cout << endl;
					return 0;
				}
				return 1;
			}
			else
			{
				cout << "Failure Message:: Drop table forget name" << endl;
				cout << endl;
				return 0;
			}
		}
		else if (word == "index")
		{
			string dropIndexName = "";
			word = getWord(str, &posi);
			if (word != "")
			{
				dropIndexName = word;
				ap.IndexDrop(dropIndexName);
				word = getWord(str, &posi);
				if (word == "")
				{
					cout << "Failure Message:: Wrong drop index format" << endl;
					cout << endl;
					return 0;
				}
				return 1;
			}
			else
			{
				cout << "Failure Message:: Failed to get index name when drop index" << endl;
				cout << endl;
				return 0;
			}
		}
		else
		{
			cout << "Failure Message:: Drop sentence wrong format" << endl;
			cout << endl;
			return 0;
		}
	}
	else if (word == "delete")
	{
		string deleteTableName = "";
		string attriName = "";
		int condition = 0;
		string value = "";

		word = getWord(str, &posi);
		if (word == "from")
		{
			word = getWord(str, &posi);
			if (word != "")
			{
				deleteTableName = word;
				word = getWord(str, &posi);
				if (word != ";")
				{
					if (word == "where")
					{
						word = getWord(str, &posi);			//写入attribute名
						if (word != "")
						{
							attriName = word;
							word = getWord(str, &posi);		//写入condition
							if (word != "")
							{
								if (word == "=")
								{
									condition = Condition::OPERATOR_EQUAL;
								}
								else if (word == "<>")
								{
									condition = Condition::OPERATOR_NOT_EQUAL;
								}
								else if (word == ">")
								{
									condition = Condition::OPERATOR_MORE;
								}
								else if (word == "<")
								{
									condition = Condition::OPERATOR_LESS;
								}
								else if (word == ">=")
								{
									condition = Condition::OPERATOR_MORE_EQUAL;
								}
								else if (word == "<=")
								{
									condition = Condition::OPERATOR_LESS_EQUAL;
								}
								else
								{
									cout << "Failure Message:: Delete sentence condition" << endl;
									cout << endl;
									return 0;
								}
								word = getWord(str, &posi);
								if (word != "")
								{
									value = word;
									Condition conditionValue(attriName, value, condition);
									ap.DeleteConditionRecord(deleteTableName, conditionValue);
								}
								else
								{
									cout << "Failure Message:: Delete sentence condition lost value" << endl;
									cout << endl;
									return 0;
								}
							}
							else
							{
								cout << "Failure Message:: Delete sentence condition lost operation" << endl;
								cout << endl;
								return 0;
							}
						}
						else
						{
							cout << "Failure Message:: Delete sentence condition lost attribute name" << endl;
							cout << endl;
							return 0;
						}
					}
					else
					{
						cout << "Failure Message:: Delete sentence wrong format of condition" << endl;
						cout << endl;
						return 0;
					}
				}
				else
				{
					ap.deleteAllRecord(deleteTableName);
				}
			}
			else
			{
				cout << "Failure Message:: Delete sentence wrong format of table name" << endl;
				cout << endl;
				return 0;
			}
		}
		else
		{
			cout << "Failure Message:: Delete sentence wrong format" << endl;
			cout << endl;
			return 0;
		}
	}
	else if (word == "quit")
	{
		ap.prepareToQuit();
		exit(1);
		return 0;
	}
	else if (word == "execfile")
	{
		string scriptFileName = "";
		word = getWord(str, &posi);
		if (word != "")
		{
			scriptFileName = word;
			word = getWord(str, &posi);
			if (word == ";")
			{
				char c;
				fstream ifn;
				ifn.open(scriptFileName);
				if (!ifn)
				{
					cout << "Failure Message:: Didn't find file!" << endl;
					cout << endl;
					return 0;
				}
				
				while (ifn.peek()!=EOF)
				{
					ifn.get(c);
					string  str1 = "";
					while (c != ';')
					{
						if (c == '\n')
						{
							ifn.get(c);
							continue;
						}
						str1 += c;
						ifn.get(c);
					}
					str1 += ';';
					cout << str1 << endl;
					InterpreterFunc(ap, str1);
				}
			}
		}
		return 1;
	}
	else
	{
		cout << "Failure Message:: Invalid input!" << endl;
		cout << endl;
		return 0;
	}
}


string Interpreter::getWord(string str, int * index)
{
	int posi1, posi2;
	string word;
	if (str[*index] == '\0')
	{
		cout << "Input Wrong!!" << endl;
		cout << endl;
		return "";
	}
	while ((str[*index] == ' ' || str[*index] == '\n' || str[*index] == '\t') && str[*index] != '\0')
	{
		(*index)++;
	}
	posi1 = *index;
	//处理括号、逗号、比较符号等有意义的符号内容
	if (str[posi1] == '(' || str[posi1] == ')' || str[posi1] == ',' || str[posi1] == '=' || str[posi1] == '<' || str[posi1] == '>' || str[posi1] == ';')
	{
		(*index)++;
		if (str[*index] == '=' || str[*index] == '>')
		{
			(*index)++;
		}
		posi2 = *index;
		word = str.substr(posi1, posi2 - posi1);
		return word;
	}
	else if (str[posi1] == '\'')		//遇到单引号返回单引号内部内容
	{
		(*index)++;
		while (str[*index] == ' ' || str[*index] == '\n' || str[*index] == '\t')//不接受单引号内部的空格等无用符号
		{
			if (str[*index] == '\0')
			{
				cout << "Input Wrong!!" << endl;
				cout << endl;
				return "";
			}
			(*index)++;
		}
		posi1 = *index;
		while (str[*index] != '\'')
		{
			if (str[*index] == '\0')
			{
				cout << "Input Wrong!!" << endl;
				cout << endl;
				return "";
			}
			(*index)++;
		}
		posi2 = *index;
		(*index)++;
		word = str.substr(posi1, posi2 - posi1);
		return word;
	}
	else
	{
		while (str[*index] != ' '&&str[*index] != '\n'&&str[*index] != '\t'&& str[*index] != '>=' && str[*index] != '<=' && str[*index] != '<>' &&str[*index] != '<'&& str[*index] != '>' &&str[*index] != '='&&str[*index] != 39 && str[*index] != '('&&str[*index] != ')'&&str[*index] != ','&&str[*index] != ';')
		{
			if (str[*index] == '\0')
			{
				cout << "Input Wrong!!" << endl;
				cout << endl;
				return "";
			}
			(*index)++;
		}
		posi2 = *index;
		if (posi1 != posi2)
		{
			word = str.substr(posi1, posi2 - posi1);
		}
		else
		{
			word = "";
		}
		return word;
	}
}