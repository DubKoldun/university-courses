package ru.ifmo.rain.epifantsev.arrayset;

import java.util.*;

public class ArraySet<T> extends AbstractSet<T> implements SortedSet<T> {

    ArraySet() {

    }

    ArraySet(Collection<? extends T> collection, Comparator<? super T> comparator) {

    }


    @Override
    public Iterator<T> iterator() {
        return null;
    }

    @Override
    public int size() {
        return size;
    }

    @Override
    public Comparator<? super T> comparator() {
        return null;
    }

    @Override
    public SortedSet<T> subSet(T fromElement, T toElement) {
        return null;
    }

    @Override
    public SortedSet<T> headSet(T toElement) {
        return null;
    }

    @Override
    public SortedSet<T> tailSet(T fromElement) {
        return null;
    }

    @Override
    public T first() {
        if (isEmpty()) {

        }
        return null;
    }

    @Override
    public T last() {
        return null;
    }

    Integer size;
}
