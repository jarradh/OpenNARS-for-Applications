/* 
 * The MIT License
 *
 * Copyright 2020 The OpenNARS authors.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

void HashTable_Test()
{
    puts(">>HashTable test start");
    HashTable_Init(&HTconcepts);
    assert(HTconcepts.VMStack.stackpointer == CONCEPTS_MAX, "The stack should be full!");
    //Insert a first concept:
    Term term1 = Narsese_Term("<a --> b>");
    Concept c1 = { .id = 1, .term = term1 };
    Concept_SetTerm(&c1, term1);
    HashTable_Set(&HTconcepts, &c1);
    assert(HTconcepts.VMStack.stackpointer == CONCEPTS_MAX-1, "One item should be taken off of the stack");
    assert(HTconcepts.HT[c1.term_hash] != NULL, "Item didn't go in right place");
    //Return it
    Concept *c1_returned = HashTable_Get(&HTconcepts, &term1);
    assert(c1_returned != NULL, "Returned item is null (1)");
    assert(Term_Equal(&c1.term, &c1_returned->term), "Hashtable Get led to different term than we put into (1)");
    //insert another with the same hash:
    Term term2 = Narsese_Term("<c --> d>");
    Concept c2 = { .id = 2, .term = term2, .term_hash = c1.term_hash }; //use different term but same hash, hash collision!
    HashTable_Set(&HTconcepts, &c2);
    //get first one:
    Concept *c1_returned_again = HashTable_Get(&HTconcepts, &term1);
    assert(c1_returned_again != NULL, "Returned item is null (2)");
    assert(Term_Equal(&c1.term, &c1_returned_again->term), "Hashtable Get led to different term than we put into (2)");
    Term term3 = Narsese_Term("<e --> f>");
    Concept c3 = { .id = 3, .term = term3, .term_hash = c1.term_hash }; //use different term but same hash, hash collision!
    HashTable_Set(&HTconcepts, &c3);
    //there should be a chain of 3 concepts now at the hash position:
    assert(Term_Equal(&HTconcepts.HT[c1.term_hash]->value->term, &c1.term), "c1 not there! (1)");
    assert(Term_Equal(&((VMItem*)HTconcepts.HT[c1.term_hash]->next)->value->term, &c2.term), "c2 not there! (1)");
    assert(Term_Equal(&((VMItem*)((VMItem*)HTconcepts.HT[c1.term_hash]->next)->next)->value->term, &c3.term), "c3 not there! (1)");
    //Delete the middle one, c2
    HashTable_Delete(&HTconcepts, &c2);
    assert(((VMItem*)HTconcepts.HT[c1.term_hash]->next)->value->id == 3, "c3 not there according to id! (2)");
    assert(Term_Equal(&HTconcepts.HT[c1.term_hash]->value->term, &c1.term), "c1 not there! (2)");
    assert(Term_Equal(&((VMItem*)HTconcepts.HT[c1.term_hash]->next)->value->term, &c3.term), "c3 not there! (2)");
    //Delete the last one, c3
    HashTable_Delete(&HTconcepts, &c3);
    assert(Term_Equal(&HTconcepts.HT[c1.term_hash]->value->term, &c1.term), "c1 not there! (3)");
    //Delete the first one, which is the last one left, c1
    HashTable_Delete(&HTconcepts, &c1);
    assert(HTconcepts.HT[c1.term_hash] == NULL, "Hash table at hash position must be null");
    assert(HTconcepts.VMStack.stackpointer == CONCEPTS_MAX, "All elements should be free now");
    puts(">>HashTable test successul");
}
