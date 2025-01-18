class ListNode {
    val: number;
    next: ListNode | null;
    constructor(val?: number, next?: ListNode | null) {
        this.val = (val === undefined ? 0 : val)
        this.next = (next === undefined ? null : next)
    };
};

function addTwoNumbers(l1: ListNode | null, l2: ListNode | null): ListNode | null {

    let list = new ListNode((l1 ? l1.val : 0) + (l2 ? l2.val : 0));
    let next: ListNode;
    if (list.val > 9) {
        list.val = list.val % 10;
        next = new ListNode(1);
    } else {
        next = new ListNode();
    }

    if (l1?.next === null && l2?.next === null) return list;
    list.next = next;
    l1 = l1 ? l1.next : null;
    l2 = l2 ? l2.next : null;

    while (l1 || l2) {


        console.log(l1, l2);
        console.log(l1?.val, l2?.val);
        
        next.val += (l1 ? l1.val : 0) + (l2 ? l2.val : 0);
        console.log(next.val);
        if (next.val > 9) { 
            next.val = next.val % 10;
            next.next = new ListNode(1);
        }
        next = next.next ? next.next : new ListNode();
        l1 = l1 ? l1.next : null;
        l2 = l2 ? l2.next : null;
    }

    return list;

};

export default function addTwoNumbersTests() {
    let i1 = new ListNode(2);
    let i2 = new ListNode(4);
    let i3 = new ListNode(3);
    i2.next= i3;
    i1.next= i2;

    let j1 = new ListNode(5);
    let j2 = new ListNode(6);
    let j3 = new ListNode(4);
    j2.next = j3;
    j1.next = j2;

    console.log(i1);
    console.log(j1);
    console.log("FINAL 1");
    console.log(addTwoNumbers(i1, j1));

    let x = new ListNode(0);
    let y = new ListNode(0);
    console.log("\n\n\nFINAL 2")
    console.log(addTwoNumbers(x,y));


    let a = new ListNode(9);
    let b = new ListNode(9);
    let c = new ListNode(9);
    let d = new ListNode(9);
    let e = new ListNode(9);
    let f = new ListNode(9);
    let g = new ListNode(9);
    f.next = g;
    e.next = f;
    d.next = e;
    c.next = d;
    b.next = c;
    a.next = b;

    let h = new ListNode(9);
    let i = new ListNode(9);
    let j = new ListNode(9);
    let k = new ListNode(9);
    j.next = k;
    i.next = j;
    h.next = i;

    console.log("\n\n\nFINAL 3")
    console.log(a, h)
    let res = addTwoNumbers(a, h);
    while (res != null) {
        console.log(res.val);
        res = res.next;
    }

    console.log("\n\n\nFINAL 4")
    a = new ListNode(8);
    b = new ListNode(3);
    c = new ListNode(2);
    b.next = c;
    a.next= b;

    d = new ListNode(9);
    e = new ListNode(2);
    f = new ListNode(1);
    e.next = f;
    d.next = e;

    console.log(a,d);
    res = addTwoNumbers(a, d);
    while (res != null) {
        console.log(res.val);
        res = res.next;
    }
}
