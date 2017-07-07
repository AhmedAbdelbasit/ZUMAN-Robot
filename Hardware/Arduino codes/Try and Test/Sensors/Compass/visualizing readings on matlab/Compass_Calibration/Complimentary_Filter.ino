void filterReading(){
  filtered_bearing = (1-filter_constant)*filtered_bearing + filter_constant*bearing;
}
