//All in millimeters

//PCB
pcb_thickness = 1;
pcb_width  = 100;
pcb_height = 160;
pcb_center_x = 0;
pcb_center_y = 0;
pcb_center_z = 0;

module CreatePcb() {
  color("Yellow")  cube(size=[pcb_width,pcb_height,pcb_thickness],center=true);
}

//Perspex
wood_thickness = 3;

//Horizontal plates

//There are three horizontal plates
// -top
// -middle
// -bottom

//Distance between bottom and middle horizontal plate
bottom_height = 50;

//Distance between middle and top horizontal plate
top_height = 50;

plate_middle_thickness = wood_thickness;
plate_middle_width  = pcb_width;
plate_middle_height = pcb_height + (2 * wood_thickness);
plate_middle_center_x = 0;
plate_middle_center_y = 0;
plate_middle_center_z = (pcb_thickness / 2) + (wood_thickness / 2);

plate_top_thickness = wood_thickness;
plate_top_width  = pcb_width;
plate_top_height = (pcb_height*0.6) + (2 * wood_thickness);
plate_top_center_x = 0;
plate_top_center_y = 0;
plate_top_center_z = plate_middle_center_z + top_height;


plate_bottom_thickness = wood_thickness;
plate_bottom_width  = pcb_width + (2 * wood_thickness);
plate_bottom_height = pcb_height + (2 * wood_thickness);
plate_bottom_center_x = 0;
plate_bottom_center_y = 0;
plate_bottom_center_z = plate_middle_center_z - bottom_height;


module CreateBottom() {
  color("Peru") cube(size=[plate_bottom_width,plate_bottom_height,plate_bottom_thickness],center=true);
}

module CreateMiddle() {
  color("Peru") cube(size=[plate_middle_width,plate_middle_height,plate_middle_thickness],center=true);
}

module CreateTop() {
  color("Peru") cube(size=[plate_top_width,plate_top_height,plate_top_thickness],center=true);
}

//Longitudinal plates
//
//    6-1
//   /   \
//  5     2 
//  |     |
//  4-----3



plate_side_x1 = plate_top_height / 2
plate_side_y1 = wood_thickness / 2
module CreateSide() {
  color("Peru") 
  polyhedron(
    points=[
      [	
    ],
    faces=[]
  );
}



//Put models in place
//PCB
translate([pcb_center_x,pcb_center_y,pcb_center_z]) { CreatePcb(); }

//Horizontal plates
//translate([plate_top_center_x,plate_top_center_y,plate_top_center_z]) { CreateTop(); }
//translate([plate_middle_center_x,plate_middle_center_y,plate_middle_center_z]) { CreateMiddle(); }
//translate([plate_bottom_center_x,plate_bottom_center_y,plate_bottom_center_z]) { CreateBottom(); }







translate([pcb_center_x,pcb_center_y,-base_height]) { CreateBase(); }