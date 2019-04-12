#pragma once
#include<iostream>
#include <list>
#include <string>
#include<vector>
#include<algorithm>
#include<ostream>

using namespace std;

string deal_cards();
string high_hand(string, string, string, string, string, string, string, string);

vector<string> Cards_out;			// cards currently in play
vector<string> Main_player;			// the main players 3 cards
vector<string> Player2;				//	player2s 3 cards (cycles 20, 50,200)
vector<string> Player3;				//	player3s 3 cards (cycles 20, 50,200)  
vector<string> Player4;				//	player4s 3 cards (cycles 20, 50,200)
vector<string> Player5;				//	player5s 3 cards (cycles 20, 50,200)
vector<string> community_cards;		// 5 community cards (cycles 20, 50,200)

string Main_player_score = "";		// the score given for best hand 
string Player2_score = "";			// 10 = royal flush, 9 = straight flush, 8 = four of a kind, 7 = full house
string Player3_score = "";			// 6 = flush, 5 = straight, 4 = three of a kind, 3 = two pair
string Player4_score = "";			// 2 = one pair, 1 = high card
string Player5_score = "";			// plus the players highest card for ties

int cycle_num = 0;
double wins = 0;
int total = 0;
double kd = 0;
string card = "";

int main()
{
	for (int lk = 1; lk < 6; lk++) {
		cout << endl <<endl << "Trial: " << lk << endl;
		cout << "the 3 cards the player gets are: "<<endl;
		for (int x = 0; x < 3; x++) {		//
			card = deal_cards();
			Main_player.push_back(card);	  // give player his 3 cards that will stay with him the whole game
			
			if (card[0] == 'e') {
				cout << "Ace of ";
			}
			if (card[0] == 'd') {
				cout << "King of ";
			}
			if (card[0] == 'c') {
				cout << "Queen of ";
			}
			if (card[0] == 'b') {
				cout << "Jack of ";
			}
			if (card[0] == 'a') {
				cout << "10 of ";
			}
			else
				cout << card[0] << " of ";

			if (card[2] == 'H') {
				cout << "Hearts" << endl;
			}
			if (card[2] == 'D') {
				cout << "Diamonds"<<endl;
			}
			if (card[2] == 'S') {
				cout << "Spades" << endl;
			}
			if (card[2] == 'C') {
				cout << "Clubs"<<endl;
			}

		}											  //
		cout << endl;


		for (int i = 0; i < 4; i++)					  // we are going to test for 20, 50, 200 and finally the final test
		{											  //
			wins = 0;
			total = 0;


			if (i == 0) { cycle_num = 20; }			  //
			else if (i == 1) { cycle_num = 50; }	  //
			else if (i == 2) { cycle_num = 200; }	  //
			else if (i == 3) { cycle_num = 1; }		  //

			for (int c = 0; c < cycle_num; c++) {		// this runs 20, 50, 200 and the final

				community_cards.clear();
				Player2.clear();
				Player3.clear();
				Player4.clear();
				Player5.clear();
				Cards_out.clear();

				for (int a = 0; a < 5; a++) { community_cards.push_back(deal_cards()); }	// gets 5 community cards

				for (int z = 0; z < 3; z++) {			//
					Player2.push_back(deal_cards());	//
					Player3.push_back(deal_cards());	// gives the 4 other players their 3 cards
					Player4.push_back(deal_cards());	//
					Player5.push_back(deal_cards());	//
				}


				Main_player_score = high_hand(Main_player[0], Main_player[1], Main_player[2], community_cards[0], community_cards[1], community_cards[2], community_cards[3], community_cards[4]);
				Player2_score = high_hand(Player2[0], Player2[1], Player2[2], community_cards[0], community_cards[1], community_cards[2], community_cards[3], community_cards[4]);
				Player3_score = high_hand(Player3[0], Player3[1], Player3[2], community_cards[0], community_cards[1], community_cards[2], community_cards[3], community_cards[4]);
				Player4_score = high_hand(Player4[0], Player4[1], Player4[2], community_cards[0], community_cards[1], community_cards[2], community_cards[3], community_cards[4]);
				Player5_score = high_hand(Player5[0], Player5[1], Player5[2], community_cards[0], community_cards[1], community_cards[2], community_cards[3], community_cards[4]);

				if (Main_player_score[0] > Player2_score[0] && Main_player_score[0] > Player3_score[0] && Main_player_score[0] > Player4_score[0] && Main_player_score[0] > Player5_score[0]) {
					total++;
					wins++;
				}
				else if (Main_player_score[0] == Player2_score[0] || Main_player_score[0] == Player3_score[0] || Main_player_score[0] == Player4_score[0] || Main_player_score[0] || Player5_score[0]) {
					if (Main_player_score[1] > Player2_score[1] && Main_player_score[1] > Player3_score[1] && Main_player_score[1] > Player4_score[1] && Main_player_score[1] > Player5_score[1]) {
						wins++;
						total++;
					}
					else {
						total++;
					}
				}
				else {
					total++;
				}






			}
			kd = (wins / total) * 100;
			if (i < 3) {
				cout << "youve won: " << wins << "  out of  " << total << ".  Which gives you a win rate of: " << kd << "%" << endl;
			}
		}
		if (wins == 1) {
			cout << "for the real game you won!" << endl;
		}
		else
			cout << "for the real game you lost :(" << endl;

	}
	return 0;
}

string deal_cards() {
	while (true) {  // continue until we get a card that is in not out already

		int rand_num = 0;		// random number for the card value 1-10 Jack, Queen, King
		int rand_face = 0;		// Random number for card face Diamond, Heart, Spade, Clubs
		string Current_card = "";

		rand_num = rand() % 13 + 1; //get a random number between 1-13 to get the card number

		if (rand_num == 10) {
			Current_card += "a ";
		}
		else if (rand_num == 1) {
			Current_card = "e ";			//
		}									//
		else if (rand_num == 11) {			//
											//
			Current_card = "b ";			//
		}									//  a = 10, b = jack,  c = queen, d= king, e = ace
		else if (rand_num == 12) {			//
											//
			Current_card = "c ";			//
		}									//
		else if (rand_num == 13) {			//
			Current_card = "d ";			//
		}
		else {
			Current_card = to_string(rand_num) + " ";   // start of the current card
		}

		rand_face = rand() % 4 + 1;		// get random number 1-4 for all face values Diamond, Heart, Spades, Clubs

		if (rand_face == 1) {				//
			Current_card += "D";			// diamonds
		}									//
		else if (rand_face == 2) {			//
			Current_card += "H";			// hearts
		}									//
		else if (rand_face == 3) {			//
			Current_card += "S";			// spades
		}									//
		else if (rand_face == 4) {			//
			Current_card += "C";			// clubs
		}

		if (Cards_out.size() == 0) {					// if the cards out vector is empty push card
			Cards_out.push_back(Current_card);			//
			return Current_card;
		}

		for (int s = 0; s < Cards_out.size(); s++) {		// check to see if card is already on the field
															//
													//
			if (Current_card == Cards_out[s]) {			// if the current card is already in the deck
				Current_card = "";							//
			}												//
			else if (s == Cards_out.size() - 1 && Current_card != "") {			// if the size of the deck 
				Cards_out.push_back(Current_card);			//
				return Current_card;						//
			}
		}
	}
}

string high_hand(string card1, string card2, string card3, string community1, string community2, string community3, string community4, string community5) {


	string player_hand = "";			// the 3 cards you hold
	string community_pile = "";			// the 5 cards in the community 
	string playing_comm_hand = ""; 			//	the 2 cards we pick to cycle
	string sorted_comm_faces = "";		// sorted 5 community cards
	string sorted_player_faces = "";	// 3 sorted player cards
	string returning = "1";				//
	int ynum = -1;						// miltiplier for y
	string full_face_tester = "";
	string full_num_tester = "";





	//sorting the cards from low to high. this is why we gave 10-ace alphabetical values.
	player_hand += card1.substr(0, card1.find(" "));
	player_hand += card2.substr(0, card2.find(" "));
	player_hand += card3.substr(0, card3.find(" "));
	community_pile += community1.substr(0, community1.find(" "));
	community_pile += community2.substr(0, community2.find(" "));
	community_pile += community3.substr(0, community3.find(" "));
	community_pile += community4.substr(0, community4.find(" "));
	community_pile += community5.substr(0, community5.find(" "));
	sort(player_hand.begin(), player_hand.end());
	sort(community_pile.begin(), community_pile.end());




	for (int x = 0; x < 5; x++)
	{
		ynum++;
		for (int y = 1; y < 5; y++)
		{
			if (y + ynum < 5)
			{
				playing_comm_hand = ""; //refresh the 2 card numerical from the community 
				sorted_comm_faces = ""; //refresh the 2 card faces from the community
				sorted_player_faces = "";//refresh the 3 card face from the player

				full_face_tester = "";
				full_num_tester = player_hand;

				// this is for a string just 2 community cards
				playing_comm_hand += community_pile[x];					// x will be 0,1,2,3,4

				playing_comm_hand += community_pile[y + ynum];				// y changes so it goes  0,1 0,2 0,3 0,4 1,2 1,3 1,4 2,3 2,4 3,4
				sort(playing_comm_hand.begin(), playing_comm_hand.end());		//

				// this is for a string of all 5 cards that 2 change
				full_num_tester += community_pile[x];					// x will be 0,1,2,3,4
				full_num_tester += community_pile[y + ynum];				// y changes so it goes  0,1 0,2 0,3 0,4 1,2 1,3 1,4 2,3 2,4 3,4
				sort(full_num_tester.begin(), full_num_tester.end());		//



					//organizes players the face value and numerical  value in linked list
				for (int h = 0; h < 3; h++) {
					if (player_hand[h] == card1[0]) { sorted_player_faces += card1[2]; }
					else if (player_hand[h] == card2[0]) { sorted_player_faces += card2[2]; }
					else if (player_hand[h] == card3[0]) { sorted_player_faces += card3[2]; }
				}

				//organizes communities the face values and numerical values in linked list
				for (int q = 0; q < 5; q++) {
					if (community_pile[q] == community1[0]) { sorted_comm_faces += community1[2]; }
					else if (community_pile[q] == community2[0]) { sorted_comm_faces += community2[2]; }
					else if (community_pile[q] == community3[0]) { sorted_comm_faces += community3[2]; }
					else if (community_pile[q] == community4[0]) { sorted_comm_faces += community4[2]; }
					else if (community_pile[q] == community5[0]) { sorted_comm_faces += community5[2]; }


				}

				// adds all the cards together
				for (int q = 0; q < 5; q++) {
					if (full_num_tester[q] == player_hand[0]) { full_face_tester += sorted_player_faces[0]; }
					else if (full_num_tester[q] == player_hand[1]) { full_face_tester += sorted_player_faces[1]; }
					else if (full_num_tester[q] == player_hand[2]) { full_face_tester += sorted_player_faces[2]; }
					else if (full_num_tester[q] == community_pile[0]) { full_face_tester += sorted_comm_faces[0]; }
					else if (full_num_tester[q] == community_pile[1]) { full_face_tester += sorted_comm_faces[1]; }
					else if (full_num_tester[q] == community_pile[2]) { full_face_tester += sorted_comm_faces[2]; }
					else if (full_num_tester[q] == community_pile[3]) { full_face_tester += sorted_comm_faces[3]; }
					else if (full_num_tester[q] == community_pile[4]) { full_face_tester += sorted_comm_faces[4]; }

				}







				//checking for a royal flush 10
				
				if (full_num_tester[4] == 'e' && full_num_tester[3] == 'd' && full_num_tester[2] == 'c' && full_num_tester[1] == 'b' && full_num_tester[0] == 'a'
					&& (full_face_tester[4] == full_face_tester[3] || full_face_tester[3] == full_face_tester[2] || full_face_tester[2] == full_face_tester[1] || full_face_tester[1] == full_face_tester[0])) {
					return "10 9";

				}

				//checking for a straight flush 9 
				if (returning[0] <= '9') {
					if (full_face_tester[4] == full_face_tester[3] && full_face_tester[3] == full_face_tester[2] && full_face_tester[2] == full_face_tester[1] && full_face_tester[1] == full_face_tester[0])
					{

						if (full_num_tester[4] == 'd' && full_num_tester[3] == 'c' &&full_num_tester[2] == 'b' && full_num_tester[1] == 'a' && full_num_tester[0] == '9') {
							returning = "9 ";
							returning += full_num_tester[4];

						}

						else if (full_num_tester[4] == 'c' && full_num_tester[3] == 'b' && full_num_tester[2] == 'a' && full_num_tester[1] == '9' && full_num_tester[0] == '8') {
							returning = "9 ";
							returning += full_num_tester[4];

						}

						else if (full_num_tester[4] == 'b' && full_num_tester[3] == 'a' && full_num_tester[2] == '9' && full_num_tester[1] == '8' && full_num_tester[0] == '7') {
							returning = "9 ";
							returning += full_num_tester[4];

						}


						else if (full_num_tester[4] == 'a' && full_num_tester[3] == '9' && full_num_tester[2] == '8' && full_num_tester[1] == '7' && full_num_tester[0] == '6') {
							returning = "9 ";
							returning += full_num_tester[4];

						}


						else if (full_num_tester[4] == '9' && full_num_tester[3] == '8' && full_num_tester[2] == '7' && full_num_tester[1] == '6' && full_num_tester[0] == '5') {
							returning = "9 ";
							returning += full_num_tester[4];

						}


						else if (full_num_tester[4] == '8' && full_num_tester[3] == '7' && full_num_tester[2] == '6' && full_num_tester[1] == '5' && full_num_tester[0] == '4') {
							returning = "9 ";
							returning += full_num_tester[4];

						}


						else if (full_num_tester[4] == '7' && full_num_tester[3] == '6' && full_num_tester[2] == '5' && full_num_tester[1] == '4' && full_num_tester[0] == '3') {
							returning = "9 ";
							returning += full_num_tester[4];

						}


						else if (full_num_tester[4] == '6' && full_num_tester[3] == '5' && full_num_tester[2] == '4' && full_num_tester[1] == '3' && full_num_tester[0] == '2') {
							returning = "9 ";
							returning += full_num_tester[4];

						}

					}
				}

				//checking for four of a kind 8
				if (returning[0] <= '8') {
					if (player_hand[0] == player_hand[1] && player_hand[1] == player_hand[2] && player_hand[2] == playing_comm_hand[0]) {
						returning = "8 ";
						returning += full_num_tester[4];
					}
					else if (player_hand[0] == player_hand[1] && player_hand[1] == player_hand[2] && player_hand[2] == playing_comm_hand[1]) {
						returning = "8 ";
						returning += full_num_tester[4];
					}
					else if (player_hand[0] == player_hand[1] && player_hand[1] == playing_comm_hand[0] && playing_comm_hand[0] == playing_comm_hand[1]) {
						returning = "8 ";
						returning += full_num_tester[4];
					}
				}

				//checking for a full house 7
				if (returning[0] <= '7') {
					if (player_hand[0] == player_hand[1] && player_hand[2] == playing_comm_hand[0] && playing_comm_hand[0] == playing_comm_hand[1]) {
						returning = "7 ";
						returning += full_num_tester[4];
					}
					if (player_hand[0] == player_hand[2] && player_hand[1] == playing_comm_hand[0] && playing_comm_hand[0] == playing_comm_hand[1]) {
						returning = "7 ";
						returning += full_num_tester[4];
					}
					if (player_hand[0] == playing_comm_hand[0] && player_hand[1] == player_hand[2] && player_hand[2] == playing_comm_hand[1]) {
						returning = "7 ";
						returning += full_num_tester[4];
					}
					if (player_hand[0] == playing_comm_hand[1] && player_hand[1] == player_hand[2] && player_hand[2] == playing_comm_hand[0]) {
						returning = "7 ";
						returning += full_num_tester[4];
					}
					if (player_hand[1] == playing_comm_hand[0] && player_hand[0] == player_hand[2] && player_hand[2] == playing_comm_hand[1]) {
						returning = "7 ";
						returning += full_num_tester[4];
					}
					if (player_hand[1] == playing_comm_hand[1] && player_hand[0] == player_hand[2] && player_hand[2] == playing_comm_hand[0]) {
						returning = "7 ";
						returning += full_num_tester[4];
					}
					if (player_hand[2] == playing_comm_hand[0] && player_hand[0] == player_hand[1] && player_hand[1] == playing_comm_hand[1]) {
						returning = "7 ";
						returning += full_num_tester[4];
					}if (playing_comm_hand[0] == playing_comm_hand[1] && player_hand[0] == player_hand[1] && player_hand[1] == player_hand[2]) {
						returning = "7 ";
						returning += full_num_tester[4];
					}


				}

				//checking for a flush 6
				if (returning[0] <= '6') {

					if (full_face_tester[4] == full_face_tester[3] && full_face_tester[3] == full_face_tester[2] && full_face_tester[2] == full_face_tester[1] && full_face_tester[1] == full_face_tester[0]) {
						returning = "6 ";
						returning += full_num_tester[4];
					}
				}

				// checking for a straight
				if (returning[0] <= '5') {
					if (full_num_tester[4] == 'd' && full_num_tester[3] == 'c' &&full_num_tester[2] == 'b' && full_num_tester[1] == 'a' && full_num_tester[0] == '9') {
						returning = "5 ";
						returning += full_num_tester[4];

					}

					else if (full_num_tester[4] == 'c' && full_num_tester[3] == 'b' && full_num_tester[2] == 'a' && full_num_tester[1] == '9' && full_num_tester[0] == '8') {
						returning = "5 ";
						returning += full_num_tester[4];

					}

					else if (full_num_tester[4] == 'b' && full_num_tester[3] == 'a' && full_num_tester[2] == '9' && full_num_tester[1] == '8' && full_num_tester[0] == '7') {
						returning = "5 ";
						returning += full_num_tester[4];

					}


					else if (full_num_tester[4] == 'a' && full_num_tester[3] == '9' && full_num_tester[2] == '8' && full_num_tester[1] == '7' && full_num_tester[0] == '6') {
						returning = "5 ";
						returning += full_num_tester[4];

					}


					else if (full_num_tester[4] == '9' && full_num_tester[3] == '8' && full_num_tester[2] == '7' && full_num_tester[1] == '6' && full_num_tester[0] == '5') {
						returning = "5 ";
						returning += full_num_tester[4];

					}


					else if (full_num_tester[4] == '8' && full_num_tester[3] == '7' && full_num_tester[2] == '6' && full_num_tester[1] == '5' && full_num_tester[0] == '4') {
						returning = "5 ";
						returning += full_num_tester[4];

					}


					else if (full_num_tester[4] == '7' && full_num_tester[3] == '6' && full_num_tester[2] == '5' && full_num_tester[1] == '4' && full_num_tester[0] == '3') {
						returning = "5 ";
						returning += full_num_tester[4];

					}


					else if (full_num_tester[4] == '6' && full_num_tester[3] == '5' && full_num_tester[2] == '4' && full_num_tester[1] == '3' && full_num_tester[0] == '2') {
						returning = "5 ";
						returning += full_num_tester[4];

					}
				}

				// checking for three of a kind
				if (returning[0] <= '4') {
					if (player_hand[0] == player_hand[1] && player_hand[1] == player_hand[2]) {
						returning = "4 ";
						returning += full_num_tester[4];
					} // xxx oo
					if (player_hand[0] == player_hand[1] && player_hand[1] == playing_comm_hand[0]) {
						returning = "4 ";
						returning += full_num_tester[4];
					} //xxo xo
					if (player_hand[0] == player_hand[1] && player_hand[1] == playing_comm_hand[1]) {
						returning = "4 ";
						returning += full_num_tester[4];
					}//xxo ox
					if (player_hand[0] == player_hand[2] && player_hand[2] == playing_comm_hand[0]) {
						returning = "4 ";
						returning += full_num_tester[4];
					}//xox xo
					if (player_hand[0] == playing_comm_hand[0] && playing_comm_hand[0] == playing_comm_hand[1]) {
						returning = "4 ";
						returning += full_num_tester[4];
					}//xox ox
					if (player_hand[1] == player_hand[2] && player_hand[2] == playing_comm_hand[0]) {
						returning = "4 ";
						returning += full_num_tester[4];
					} // oxx xo
					if (player_hand[1] == player_hand[2] && player_hand[2] == playing_comm_hand[1]) {
						returning = "4 ";
						returning += full_num_tester[4];
					}// oxx ox
					if (player_hand[1] == playing_comm_hand[0] && playing_comm_hand[0] == playing_comm_hand[1]) {
						returning = "4 ";
						returning += full_num_tester[4];
					} // oxo xx
					if (player_hand[2] == playing_comm_hand[0] && playing_comm_hand[0] == playing_comm_hand[1]) {
						returning = "4 ";
						returning += full_num_tester[4];
					} //oox xx
					if (player_hand[0] == playing_comm_hand[0] && playing_comm_hand[0] == playing_comm_hand[1]) {
						returning = "4 ";
						returning += full_num_tester[4];
					} //xoo xx



				}

				//checking for 2 pairs
				if (returning[0] <= '3') {
					if (player_hand[0] == player_hand[1]) {
						if (player_hand[2] == playing_comm_hand[0] || player_hand[2] == playing_comm_hand[1]) {
							returning = "3 ";
							returning += full_num_tester[4];
						}
					} //
					if (player_hand[0] == player_hand[2]) {
						if (player_hand[1] == playing_comm_hand[0] || player_hand[1] == playing_comm_hand[1]) {
							returning = "3 ";
							returning += full_num_tester[4];
						}
					} //
					if (player_hand[0] == playing_comm_hand[0]) {
						if (player_hand[1] == player_hand[2] || player_hand[2] == playing_comm_hand[0] || player_hand[2] == playing_comm_hand[1]) {
							returning = "3 ";
							returning += full_num_tester[4];
						}
					} // 
					if (player_hand[0] == playing_comm_hand[1]) {
						if (player_hand[1] == player_hand[2] || player_hand[2] == playing_comm_hand[0] || player_hand[2] == playing_comm_hand[1]) {
							returning = "3 ";
							returning += full_num_tester[4];
						}
					} //
					if (player_hand[1] == player_hand[2]) {
						if (player_hand[0] == playing_comm_hand[0] || player_hand[0] == playing_comm_hand[1]) {
							returning = "3 ";
							returning += full_num_tester[4];
						}
					}//
					if (player_hand[1] == playing_comm_hand[0]) {
						if (player_hand[0] == player_hand[2] || player_hand[0] == playing_comm_hand[0] || player_hand[0] == playing_comm_hand[1] || player_hand[2] == playing_comm_hand[0] | player_hand[2] == playing_comm_hand[1]) {
							returning = "3 ";
							returning += full_num_tester[4];
						}
					} //
					if (player_hand[1] == playing_comm_hand[1]) {
						if (player_hand[0] == player_hand[2] || player_hand[0] == playing_comm_hand[0] || player_hand[0] == playing_comm_hand[1] || player_hand[2] == playing_comm_hand[0] | player_hand[2] == playing_comm_hand[1]) {
							returning = "3 ";
							returning += full_num_tester[4];
						}
					} // oxo ox
					if (player_hand[2] == playing_comm_hand[0]) {
						if (player_hand[0] == player_hand[1] || player_hand[0] == playing_comm_hand[1] || player_hand[1] == playing_comm_hand[1]) {
							returning = "3 ";
							returning += full_num_tester[4];
						}
					}// oox xo
					if (player_hand[2] == playing_comm_hand[1]) {
						if (player_hand[0] == player_hand[1] || player_hand[0] == playing_comm_hand[0] || player_hand[1] == playing_comm_hand[1]) {
							returning = "3 ";
							returning += full_num_tester[4];
						}
					} //oox ox
				}



				//check for 1 pair
				if (returning[0] <= '2') {
					if (player_hand[0] == player_hand[1]) {
						returning = "2 ";
						returning += full_num_tester[4];
					} //xxo oo
					if (player_hand[0] == player_hand[2]) {
						returning = "2 ";
						returning += full_num_tester[4];
					} //xox oo
					if (player_hand[0] == playing_comm_hand[0]) {
						returning = "2 ";
						returning += full_num_tester[4];
					} // xoo xo
					if (player_hand[0] == playing_comm_hand[1]) {
						returning = "2 ";
						returning += full_num_tester[4];
					} //xoo ox
					if (player_hand[1] == player_hand[2]) {
						returning = "2 ";
						returning += full_num_tester[4];
					}//oxx oo
					if (player_hand[1] == playing_comm_hand[0]) {
						returning = "2 ";
						returning += full_num_tester[4];
					} //oxo xo
					if (player_hand[1] == playing_comm_hand[1]) {
						returning = "2 ";
						returning += full_num_tester[4];
					} // oxo ox
					if (player_hand[2] == playing_comm_hand[0]) {
						returning = "2 ";
						returning += full_num_tester[4];
					}// oox xo
					if (player_hand[2] == playing_comm_hand[1]) {
						returning = "2 ";
						returning += full_num_tester[4];
					} //oox ox
				}

				//giving highest card
				if (returning[0] <= '1') {
					if (x == 3 && (y == 1)) {
						returning = "1 ";
						returning += full_num_tester[4];
					}
				}
			}
		}
	}
	return returning;
}
