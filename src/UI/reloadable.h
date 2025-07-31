#ifndef RELOADABLE_H
#define RELOADABLE_H

class Reloadable {
public:
	virtual ~Reloadable() = default;
	virtual void reload() = 0;
};

#endif // RELOADABLE_H
