// template.scad


$fn=60;

// variables

// variable 1
d1 = 10;    // [1:1:100]
// variable 2
l1 = 65;    // [5:1:80]
// variable 3
l2 = 28;    // [1:1:69]


main();


module main()
{
    
//    translate([50,0,0])cube_r(30,20,10,2);
//    
//    translate([0,50,0])rotate([90,0,0])rectTriangle(10,20,5);
//    
//    linear_extrude(12)translate([10,10,0])import("BFKDO.svg");
//    
//    translate([50,50,0])rotate([0,0,0])linear_extrude(height = 0.5)text("(c) ChB 2/2021",size = 5);
//    
//    translate([100,0,0])cylinder_r(40,12,8,3,2);
    
    difference(){
        plus();
        minus();

    }
}


module plus()
{   
    translate([0,0,0])rotate([0,0,0])cube([52,62,18]);
    translate([116-52,0,0])rotate([0,0,0])cube([52,62,18]);
    translate([0,0,0])rotate([0,0,0])cube([116,62,10]);
//    translate([0,0,12])rotate([0,0,0])cylinder(l1,12/2,11.8/2);
    

}

module minus()
{
//    translate([0,0,12])rotate([0,0,0])cylinder(4,12/2,11.8/2);
    translate([5,10,0])rotate([0,0,0])cube([42.45,42.4,20]);
    translate([116-52+5,10,0])rotate([0,0,0])cube([42.45,42.4,20]);
    
    translate([116/2,10,0])rotate([0,0,0])cylinder(20,4/2,4/2);
    translate([116/2,10,9])rotate([0,0,0])cylinder(2,4/2,9/2);
    
    translate([116/2,52,0])rotate([0,0,0])cylinder(20,4/2,4/2);
    translate([116/2,52,9])rotate([0,0,0])cylinder(2,4/2,9/2);
    
    translate([42/2+5,12,0])rotate([90,0,0])cylinder(20,20/2,20/2);
    translate([116-(42/2+5),12,3])rotate([90,0,0])cylinder(20,22/2,22/2);
    
}

module cube_r(x,y,z,r)
{
    hull()
    {
        translate([r,r,r])cube([x-2*r,y-2*r,z-2*r]);
        translate([r,r,r])rotate([0,0,0])cylinder(z-2*r,r,r);
        translate([r,y-r,r])rotate([0,0,0])cylinder(z-2*r,r,r);
        translate([x-r,r,r])rotate([0,0,0])cylinder(z-2*r,r,r);
        translate([x-r,y-r,r])rotate([0,0,0])cylinder(z-2*r,r,r);
        
        translate([r,r,r])rotate([0,90,0])cylinder(x-2*r,r,r);
        translate([r,y-r,r])rotate([0,90,0])cylinder(x-2*r,r,r);
        translate([r,y-r,z-r])rotate([0,90,0])cylinder(x-2*r,r,r);
        translate([r,r,z-r])rotate([0,90,0])cylinder(x-2*r,r,r);
        
        translate([x-r,y-r,r])rotate([90,0,0])cylinder(y-2*r,r,r);
        translate([r,y-r,r])rotate([90,0,0])cylinder(y-2*r,r,r);
        translate([r,y-r,z-r])rotate([90,0,0])cylinder(y-2*r,r,r);
        translate([x-r,y-r,z-r])rotate([90,0,0])cylinder(y-2*r,r,r);
        
        translate([r,r,r])sphere(r = r);
        translate([x-r,r,r])sphere(r = r);
        translate([r,y-r,r])sphere(r = r);
        translate([x-r,y-r,r])sphere(r = r);
        
        translate([r,r,z-r])sphere(r = r);
        translate([x-r,r,z-r])sphere(r = r);
        translate([r,y-r,z-r])sphere(r = r);
        translate([x-r,y-r,z-r])sphere(r = r);
    }
}

module cylinder_r(h,r1,r2,r3,r4)
{
    hull()
    {
        translate([0,0,r3])cylinder(h-r3-r4,r1-r3,r2-r4);
        
        translate([0,0,r3])rotate_extrude(convexity = 10, $fn = 100)
            translate([r1, 0, 0])circle(r = r3, $fn = 100);
        
        translate([0,0,h-r4])rotate_extrude(convexity = 10, $fn = 100)
            translate([r2, 0, 0])circle(r = r4, $fn = 100);
    }
    
}

module rectTriangle(a,b,h)
{
linear_extrude(height = h, center = false, convexity = 10, twist = 0)
    polygon(points=[[0,0],[a,0],[0,b]]);   
}


