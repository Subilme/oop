using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OOPLab7
{
    public class MyList<T> : IEnumerable<T>
    {

        public Node<T> first;
        private Node<T> _last;

        public MyList()
        {
            first = null;
            _last = first;
        }

        public MyList(IEnumerable<T> list)
        {
            first = null;
            _last = new Node<T>();
            foreach(T elem in list)
            {
                Node<T> newNode = new Node<T>();
                newNode.Value = elem;
                newNode.Next = null;
                if (first == null)
                {
                    first = newNode;
                    first.Prev = null;
                    _last = first;
                    continue;
                }
                _last.Next = newNode;
                newNode.Prev = _last;
                _last = _last.Next;
            }
        }

        public T this[int index]
        {
            get
            {
                Node<T> elem = GetByIndex(index);
                return elem.Value;
            }
            set
            {
                Node<T> elem = GetByIndex(index);
                elem.Value = value;
            }
        }

        public int Count()
        {
            if (first == null)
            {
                return 0;
            }
            int counter = 0;
            Node<T> node = first;
            while (node.Next != null)
            {
                counter++;
                node = node.Next;
            }
            return counter;
        }

        public bool Contain(T elem)
        {
            return GetByValue(elem) != null;
        }

        public void PushFront(T value)
        {
            Node<T> newNode = new Node<T>();
            newNode.Value = value;
            newNode.Prev = null;
            if (first == null)
            {
                newNode.Next = null;
                first = newNode;
                _last = first;
                return;
            }
            newNode.Next = first;
            first.Prev = newNode;
            first = newNode;
        }

        public void PushBack(T value)
        {
            Node<T> newNode = new Node<T>();
            newNode.Value = value;
            newNode.Next = null;
            if (first == null)
            {
                newNode.Prev = null;
                first = newNode;
                _last = first;
                return;
            }
            newNode.Prev = _last;
            _last.Next = newNode;
            _last = newNode;
        }

        public void Insert()
        {

        }

        public void Remove(T elem)
        {
            Node<T> newNode = GetByValue(elem);
            Remove(newNode);
        }

        public void Remove(Node<T> elem)
        {

        }

        private Node<T> GetByIndex(int index)
        {
            Node<T> elem = first;
            int counter = 0;
            while (counter < index)
            {
                if (elem.Next == null)
                {
                    throw new IndexOutOfRangeException();
                }
                elem = elem.Next;
                counter++;
            }
            return elem;
        }

        private Node<T> GetByValue(T value)
        {
            Node<T> elem = first;
            while (elem.Next != null)
            {
                if (elem.Value.Equals(value))
                {
                    return elem;
                }
            }
            return null;
        }

        public IEnumerator<T> GetEnumerator()
        {
            return new MyListEnumerator<T>(this);
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return new MyListEnumerator<T>(this);
        }
    }
}
