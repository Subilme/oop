using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OOPLab7
{
    public class Node<T>
    {
        public Node<T> Prev { get; set; } = null;
        public Node<T> Next { get; set; } = null;
        public T Value { get; set; }
    }
}
