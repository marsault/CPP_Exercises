#pragma once

// Il est interdit de modifier ce fichier !!

/**
 * La classe `Tracker` compte le nombre d'objets de type Tracker en mémoire.
 */
class Tracker
{
public:
  Tracker()
      : _id{_next_id++}
  {
    ++_count;
  }

  Tracker(const Tracker& other)
      : _id{other._id}
  {
    ++_count;
    ++_copies;
  }

  Tracker& operator=(const Tracker& other)
  {
    if (this != &other) {
      _id = other._id;
      ++_copies;
    }
    return *this;
  }

  Tracker(Tracker&& other) noexcept
      : _id{other._id}
  {
    other._id = 0;
    _count++;
  }

  Tracker& operator=(Tracker&& other) noexcept
  {
    if (this != &other) {
      _id = other._id;
      other._id = 0;
    }
    return *this;
  }

  ~Tracker() { --_count; }


  int tracker_id() const { return _id; }

  // Deux Tracker sont égaux s'ils ont le même _id
  bool operator==(const Tracker& other) const { return (_id == other._id); }
  bool operator!=(const Tracker& other) const { return !(*this == other); }


  static int count() { return _count; }
  static int copies() { return _copies; }

private:
  int _id;

  inline static int _count = 0;  // Compte le nombre d'instance de Tracker en mémoire.
  inline static int _copies = 0; // Compte le nombre de fois que des Tracker ont été copiée.
  inline static int _next_id = 1;
};

// Il est interdit de modifier ce fichier !!
