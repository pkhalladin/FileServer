#pragma once

class CommandLine
{
public:
	CommandLine(int port, bool isRemote);

	bool TryParse(int argc, char** argv);
	int GetPort() const;
	bool IsRemote() const;
private:
	int port;
	bool isRemote;
};
