#include <iostream>
#include <string>

class User {
public:
  /**
   * Creates a new User with the given name and no friends.
   */
  User(const std::string& name);

  /**
   * Destructor.
   */
  ~User();

  /**
   * Copy constructor.
   */
  User(const User& other);

  /**
   * Copy assignment operator.
   */
  User& operator=(const User& other);

  /**
   * Move constructor.
   */
  User(User&&) = delete;

  /**
   * Move assignment operator.
   */
  User& operator=(User&&) = delete;

  /**
   * Adds a friend to this User's list of friends.
   * @param name The name of the friend to add.
   */
  void add_friend(const std::string& name);

  /**
   * Returns the name of this User.
   */
  std::string get_name() const;

  /**
   * Returns the number of friends this User has.
   */
  size_t size() const;

  /**
   * Sets the friend at the given index to the given name.
   * @param index The index of the friend to set.
   * @param name The name to set the friend to.
   */
  void set_friend(size_t index, const std::string& name);

  /**
   * Overloads the << operator to print the User's information.
   */
  friend std::ostream& operator<<(std::ostream& os, const User& user);

  /**
   * Overloads the += operator to add a user to another user's friend list symmetrically.
   */
  User& operator+=(User& other);

  /**
   * Overloads the < operator to compare users alphabetically by name.
   */
  bool operator<(const User& other) const;

private:
  std::string _name;
  size_t _capacity;
  size_t _size;
  std::string* _friends;

  /**
   * Copies friends to this instance. Assumes `_capacity` and `_size` are set appropriately
   * beforehand.
   */
  void set_friends(const std::string* other_friends);
};
