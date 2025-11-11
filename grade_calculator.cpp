// These headers define some of the classes and functions we need
#include <iostream>
#include <string>
#include <sstream>
#include <limits>

// ONLY MAKE CHANGES WHERE THERE IS A TODO(student)

// These using declarations let us refer to things more simply
// e.g. instead of "std::cin" we can just write "cin"
using std::cin, std::cout, std::endl;
using std::string, std::getline;

// These methods are defined below the main function

// print instructions for inputting grades
void print_instructions();

// pretty print a summary of the grades
void print_results(double exam_average,
                   double hw_average,
                   double lw_average,
                   double reading,
                   double engagement,
                   double weighted_total,
                   char final_letter_grade);

// extract the category and score from the line
// and store the values in the provided variables
// if line := "exam 95", then category := "exam" and score := 95
// if the line is invalid, then category := "ignore"
void get_category_and_score(const string& line,
                            string* category,
                            double* score);

int main() {
    print_instructions();

    // ONLY MAKE CHANGES WHERE THERE IS A TODO(student)

    double total_exam=0;
    double exam_count=0;
    double total_hw=0;
    double hw_count=0;
    double total_lw=0;
    double lw_count=0;
    double reading_total=0;
    double engagement_total=0;
    
    double engagement_count=0;
    double finalexam=0;

    double max_score=0;
    double second_max_score=0;
    
    double reading_count=0; 
    double midterm_avg;
    double weighted_total=0;


    string line;
    // read one line from standard input (discards the ending newline character)
    getline(cin, line);
    // read lines until an empty line is read
    while (!line.empty()) {
        string category;
        double score;
        get_category_and_score(line, &category, &score);

        // process the grade entry
        if (category == "exam") {
            exam_count++;
            if (score>max_score){
                second_max_score=max_score;
                max_score=score;
            } else if (score>second_max_score){
                second_max_score=score;
            }
        } else if (category == "final-exam") {
            finalexam=score;
        } else if (category == "hw") {
                total_hw+=score;
                hw_count++;
        }
        else if (category == "lw") {
            if (score>=50){
                total_lw+=100;
            }
            else {
                total_lw+=0;
            }
            lw_count++;
        } else if (category == "reading") {
            score=score*100;
            reading_total+=score;
            reading_count++;
        } else if (category == "engagement") {
            if (score>0){
                engagement_total+=100;
            }else{
                engagement_total+=0;
            }
            engagement_count++;
        } else {
            cout << "ignored invalid input" << endl;
        }

        // get the next line from standard input
        getline(cin, line);
    }

    double hw_average = 0;
    double lw_average = 0;
    double exam_average = 0;
    double reading_average = 0;
    double engagement_average = 0;

    midterm_avg= (max_score+second_max_score)/2;
    exam_average=midterm_avg*0.6+finalexam*.4;

    if (hw_count>0){
      hw_average=total_hw/hw_count;
    } else{
        hw_average=0;
    }
    if (lw_count>0){
        lw_average=total_lw/lw_count;
    } else{
     lw_average=0;
        }
    if (reading_count>0){
        reading_average=(reading_total/reading_count);
    }
    else{
        reading_average=15;
    }
    if(engagement_count>0){
        engagement_average=(engagement_total/engagement_count);
    }
    else{
        engagement_average=15;
    }
    if(exam_count>0){
        midterm_avg=total_exam/exam_count;    
    }

    if (hw_average>100){
        hw_average=100;
    }
    if (lw_average>100){
        lw_average=100;
    }
    if (exam_average>100){
        exam_average=100;
    }
    if (engagement_average>85){
        engagement_average=100;
    }
    else if (engagement_count>0){
        engagement_average+=15;
    }
    if (reading_average>85){
        reading_average=100;
    }
    else if (reading_count>0){
        reading_average+=15;
    }
    //TODO(student): compute component averages and assign to the above variables
    // exam_average = ???; // etc.

    // TODO(student): compute weighted total of components
   
    weighted_total=exam_average*0.6+hw_average*.2+lw_average*.1+reading_average*.05+engagement_average*0.05;
    
    // TODO(student): compute final letter grade
    char final_letter_grade = 'X';
    if (weighted_total>=89.5){
        final_letter_grade='A';
    } else if (weighted_total>=79.5){
        final_letter_grade='B';
    } else if (weighted_total>=69.5){
        final_letter_grade='C';
    }else if (weighted_total>=59.5){
        final_letter_grade='D';
    }else {
        final_letter_grade='F';
    }
    // Do not modify print_results since this will not help
    print_results(
        exam_average, hw_average, lw_average, reading_average, engagement_average,
        weighted_total, final_letter_grade);
}

// These methods are already implemented for you
// You should not need to modify them
// Even minor changes might cause you to fail test cases for the wrong reasons

void print_instructions() {
    cout << "enter grades as <category> <score>" << endl;
    cout << "  <category> := exam | final-exam | hw | lw | reading | engagement" << endl;
    cout << "     <score> := numeric value" << endl;
    cout << "enter an empty line to end input" << endl;
}

// YOU ARE NOT EXPECTED TO UNDERSTAND THIS ONE... YET
void get_category_and_score(
    const string& line,
    string* category,
    double* score) {
    // turn the string into an input stream
    std::istringstream sin(line);

    // read the category (as string) and score (as double) from the stream
    sin >> *category;
    sin >> *score;

    if (sin.fail()) {
        // the stream is in a fail state (something went wrong)
        // clear the flags
        sin.clear();
        // clear the stream buffer (throw away whatever garbage is in there)
        sin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        // signal that the line was invalid
        *category = "ignore";
    }
}

void print_results(
    double exam_average,
    double hw_average,
    double lw_average,
    double reading,
    double engagement,
    double weighted_total,
    char final_letter_grade) {
    cout << "summary:" << endl;
    cout << "        exam average: " << exam_average << endl;
    cout << "          hw average: " << hw_average << endl;
    cout << "          lw average: " << lw_average << endl;
    cout << "     reading average: " << reading << endl;
    cout << "  engagement average: " << engagement << endl;
    cout << "  -------------------" << endl;

    cout << "      weighted total: " << weighted_total << endl;

    cout << "  final letter grade: " << final_letter_grade << endl;
}
