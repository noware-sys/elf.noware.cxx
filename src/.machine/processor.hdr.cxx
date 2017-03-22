//#pragma once

//namespace noware
//{
	//namespace machine
	//{
		class processor : public device
		{
			public:
				enum/* class*/ operation
				{
					none,
					// For controlling the flow of the execution:
					// and, intersection
					// or, union
					
					obtainment,	// attainment obtainment
					assignment,
					//presence,
					removal,	// removal resettal
					
					addition,
					substraction,
					multiplication,
					division,
					
					exponentiation
					modulo,
					modulus,
					complement,
					
					//output	// output set echo
					//jump,
				};
				
				class instruction
				{
					public:
						instruction (void);
						~instruction (void);
						
						operation operation;	// Optional.
						noware::var operand1;
						noware::var operand2;	// Optional.
						
						//dependents;	// Not really needed.
						//dependencies;
						
						//const bool operator== (const instruction &/* other*/) const;
						const noware::var evaluate (void) const;
				};
				
				processor (void);
				~processor (void);
				
				// dequeue beginning first head top pop next fetch operate
				const instruction next (void) const;
				const bool dequeue (void);
				//const instruction dequeue (void);
				const bool enqueue (const instruction &);
				//const bool enqueue (const operation &, const noware::var &/* operand1*/, const noware::var &/* operand2*/ = "");	// Accurate.
				const bool enqueue (const noware::var &/* operand1*/, const operation &/* operator*/ = operation::none, const noware::var &/* operand2*/ = "");
				//const bool apply (const instruction &);
		};
	//}
//}

/*
	{
		(ins(req()));
		(ins(req()));
		(ins(req()));
	}
*/

/*
	activity
	{
		process (exp (ins));
		process (exp (ins));
		process (exp (ins));
	}
*/

/*
*/
