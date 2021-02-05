template <class T> class list;
template <class  T>
void	swap(T& a, T& b) noexcept
{
	T c(a);
	a = b;
	b = c;
}

template <class T>
void	tricky_swap(list<T>& l1, list<T>& l2)
{
	swap(l1._head, l2._head);
	swap(l1._tail, l2._tail);
	swap(l1._size, l2._size);
}