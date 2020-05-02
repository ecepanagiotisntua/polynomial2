#include <iostream>
#include <cmath>


using namespace std;

class Polynomial {
protected:
    class Term {
    protected:
        int exponent;
        int coefficient;
        Term *next;
        Term(int exp, int coeff, Term *n) {
          exponent = exp;
          coefficient = coeff;
          next = n;
        }

        friend class Polynomial;

        friend Polynomial operator + (const Polynomial &p, const Polynomial &q);

        friend Polynomial operator * (const Polynomial &p, const Polynomial &q);

        friend ostream & operator << (ostream &out, const Polynomial &p);
    };

      Term *head;

      void copy(const Polynomial &p) {
        for(Term *t = p.head; t != nullptr; t = t->next)
          push_back(t->exponent, t->coefficient);
      }

      void push_back(const int &exp, const int &coeff) {
        Term *t = new Term(exp, coeff, nullptr);
        Term *p;

        if (head == nullptr) {
          head = t;
          return;
        }

        p = head;
        while (p != nullptr && p->next != nullptr)
          p = p->next;
        p->next = t;
      }

public:
    Polynomial() { head = nullptr; }

    Polynomial(const Polynomial &p) {
    head = nullptr;
    copy(p);
  }

    ~Polynomial() { delete head; }

	Polynomial & operator = (const Polynomial &p) {
		if (this == &p) { return *this; }
		delete head;
		head = nullptr;
		Term *target = p.head;
		while (target != nullptr) {
			this->addTerm(target->exponent, target->coefficient);
			target = target->next;
		}
		return *this;
	}

    void addTerm(int expon, int coeff) {
        Term *n = new Term(expon, coeff, nullptr);
        Term *p, *q;

        if (coeff == 0) {
          delete n;
          return;
        }

        if (head == nullptr) {
          head = n;
          return;
        }

        if (head->exponent == expon) {
            head->coefficient += coeff;
            if(head->coefficient == 0) {
                p = head;
                head = head->next;
                delete p;
            }
            delete n;
            return;
        }

        p = head;
        q = p->next;
        while (q != nullptr && q->exponent > expon) {
            p = q;
            q = q->next;
        }
        if (q != nullptr && q->exponent == expon) {
            q->coefficient += coeff;
            if(q->coefficient == 0) {
                p->next = q->next;
                delete q;
            }
            delete n;
            }
        else {
            if (n->exponent < p->exponent) {
                n->next = p->next;
                p->next = n;
            }
            else {
                n->next = p;
                head = n;
            }
        }
    }

	double evaluate(double x) {
		Term *target = head;
		double sum = 0;
		while (target != nullptr) {
			sum += target->coefficient * pow(x, target->exponent);
			target = target->next;
		}
		return sum;
	}

    friend Polynomial operator + (const Polynomial &p, const Polynomial &q) {
        Polynomial Poly;
        Term *i, *j, *k;
        i = p.head;
        j = q.head;
        while(i != nullptr && j != nullptr) {
            if (i->exponent > j->exponent) {
                Poly.push_back(i->exponent, i->coefficient);
                i = i->next;
            }
            else if (i->exponent < j->exponent) {
                Poly.push_back(j->exponent, j->coefficient);
                j = j->next;
            }
            else {
                Poly.addTerm(i->exponent, i->coefficient + j->coefficient);
                i = i->next;
                j = j->next;
            }
        }

        if (i == nullptr) { k = j; }
        else if (j == nullptr) { k = i; }
        while (k != nullptr) {
            Poly.push_back(k->exponent, k->coefficient);
            k = k->next;
        }
        return Poly;
      }

      friend Polynomial operator * (const Polynomial &p, const Polynomial &q) {
        Polynomial Poly;
        for (Term *i = p.head; i != nullptr; i = i->next)
            for (Term *j = q.head; j != nullptr; j = j->next)
                Poly.addTerm(i->exponent + j->exponent, i->coefficient * j->coefficient);
        return Poly;
      }

      friend ostream & operator << (ostream &out, const Polynomial &p) {
        Term *n = p.head;

        if(n == nullptr) {
          out << 0;
          return out;
        }
        if (n->coefficient < 0) { out << "- "; }

        if (abs(n->coefficient) != 1) {out << abs(n->coefficient); }

        if (n->exponent == 0 && abs(n->coefficient) == 1) { out << "1"; }

        if (n->exponent == 1) { out << "x"; }
        else if (n->exponent != 0) { out << "x^" << n->exponent; }
        n = n->next;
        while(n != nullptr) {
          if (n->coefficient < 0) {out << " - ";}
          else { out << " + "; }

          if (abs(n->coefficient) != 1) { out << abs(n->coefficient); }
          else if (n->exponent == 0) { out << abs(n->coefficient); }

          if(n->exponent == 1) {out << "x"; }
          else if(n->exponent != 0) {out << "x^" << n->exponent; }
          n = n->next;
      }

        return out;
      }
};
