using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OOPLab7
{
    public class MyListEnumerator<T> : IEnumerator<T>
    {
        private readonly MyList<T> _list;
        private Node<T> _first;
        private Node<T> _last;

        public MyListEnumerator(MyList<T> list)
        {
            _list = list;
            _first = _list.first;
            _last = null;
        }
        public T Current => throw new NotImplementedException();

        object IEnumerator.Current => throw new NotImplementedException();

        public void Dispose()
        {
            throw new NotImplementedException();
        }

        public bool MoveNext()
        {
            throw new NotImplementedException();
        }

        public void Reset()
        {
            throw new NotImplementedException();
        }
    }

    public class MyListReverseEnumerator<T> : IEnumerator<T>
    {
        private readonly MyList<T> _list;
        private Node<T> _last;
        private Node<T> _first;

        public ()

        public T Current => throw new NotImplementedException();

        object IEnumerator.Current => throw new NotImplementedException();

        public void Dispose()
        {
            throw new NotImplementedException();
        }

        public bool MoveNext()
        {
            throw new NotImplementedException();
        }

        public void Reset()
        {
            throw new NotImplementedException();
        }
    }
}
