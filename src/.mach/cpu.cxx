#pragma once

//#include "processor.hdr.cxx"

const std::string noware::mach::cpu::grp_dft = "noware::mach::cpu";

noware::mach::cpu::instr::instr (void)
{
	//oprn = opr::none;
	//device = dev::none;
	opr = "";
	dev = "";
	
	//oprnd [0] = oprnd [1] = "";
	////oprnd_src_ref = false;
	//ref [0] = ref [1] = false;
	
	thread_id = "";
}

noware::mach::cpu::instr::instr (const std::string & other)
{
	//oprn = opr::none;
	//deserialize (other);
	*this = other;
}

noware::mach::cpu::instr::~instr (void)
{
}

template <typename archive>
void noware::mach::cpu::instr::serialize (archive & arch, const unsigned int &/* version*/)
{
	//arch & oprn;
	//arch & device;
	arch & opr;
	arch & dev;
	
	arch & arg;
	arch & arg_type;
	
	/*
	arch & oprnd [0];
	arch & oprnd [1];
	//arch & oprnd [2];
	
	arch & _ref [0];
	arch & _ref [1];
	
	arch & _offset [0];
	arch & _offset [1];
	
	arch & offset [0];
	arch & offset [1];
	*/
	
	arch & thread_id;
	
	//arch & oprnd_src_ref;
}

const bool noware::mach::cpu::instr::deserialize (const std::string & serial)
{
	return noware::deserialize <noware::mach::cpu::instr> (*this, serial);
}

const std::string noware::mach::cpu::instr::serialize (void) const
{
	std::string serial;
	
	if (noware::serialize <noware::mach::cpu::instr> (serial, *this))
		return serial;
	else
		return "";
}

const std::string noware::mach::cpu::instr::val (void) const
{
	//return oprnd [0];
	return "";
}

const noware::mach::cpu::instr & noware::mach::cpu::instr::operator = (const instr & other)
{
	opr = other.opr;
	dev = other.dev;
	
	arg = other.arg;
	arg_type = other.arg_type;
	
	/*
	oprnd [0] = other.oprnd [0];
	oprnd [1] = other.oprnd [1];
	
	ref [0] = other.ref [0];
	ref [1] = other.ref [1];
	*/
	
	thread_id = other.thread_id;
	
	return *this;
}

const std::string & noware::mach::cpu::instr::operator = (const std::string & other)
{
	deserialize (other);
	return other;
}

noware::mach::cpu::instr::operator const std::string (void) const
{
	return serialize ();
}

noware::mach::cpu::cpu (void)
{
	running = false;
	exen = nullptr;
	//assert (node.join (grp_dft));
	//node.join ("noware::mach::thread::1");
}

noware::mach::cpu::~cpu (void)
{
	stop ();
}

const bool noware::mach::cpu::stop (void)
{
	if (!status ())
		return true;
	
	running = false;
	exen -> join ();
	delete exen;
	exen = nullptr;
	
	return true;
}

const bool noware::mach::cpu::status (void) const
{
	return exen != nullptr;
}

const bool noware::mach::cpu::start (void)
{
	if (status ())
		return true;
	
	running = true;
	exen = new boost::thread (boost::bind (boost::mem_fn (&noware::mach::cpu::exe), this));
	
	return true;
}

void noware::mach::cpu::exe (void)
{
	std::cerr << "noware::mach::cpu::exe()::in scope" << std::endl;
	
	instr inst;
	instr inst_next;
	
	noware::nr index_max;
	noware::nr index;
	
	//noware::var src;
	//noware::var dest;
	
	//noware::var src_offset;
	//noware::var dest_offset;
	
	char delimiter;
	std::string input;
	
	std::string thread_id;
	
	bool result;
	
	/*
	//zmq::msg msg_thread;
	std::map <std::string, std::string> map_thread;
	std::string map_thread_serial;
	zmq::msg msg;
	
	map_thread ["subject"] = "notification";
	map_thread ["success"] = "1";
	
	noware::serialize <std::map <std::string, std::string>> (map_thread_serial, map_thread);
	
	msg = map_thread_serial;
	
	msg.prepend (zmq::msg::frame ("dummy_request_token"));
	*/
	
	result = false;
	
	//while (true)
	while (running)
	{
		std::cerr << "noware::mach::cpu::exe()::while(true)::in scope" << std::endl;
		std::cerr << "noware::mach::cpu::exe()::while(running)::in scope" << std::endl;
		
		while (!empty ())
		{
			std::cerr << "noware::mach::cpu::exe()::while(!empty())::in scope" << std::endl;
			
			// fetch next (and dequeue)
			std::cerr << "noware::mach::cpu::next_dequeue()" << std::endl;
			inst = next_dequeue ();
			
			// decode
			thread_id = std::string ("thread ") + inst.thread_id;
			
			// execute
			//inst.val ();
			/*
			if (inst.oprnd_src_ref)
			{
				inst.oprnd [0] = get (inst.oprnd [0]);
			}
			*/
			//set (inst.oprnd [2]/* group*/, inst.oprnd [1]/* key*/, inst.oprnd [0]/* value*/);
			////set (grp, inst.oprnd [1]/* key*/, inst.oprnd [0]/* value*/);
			//if ()
			//set (inst.oprnd [2]/* group*/, inst.oprnd [1]/* key*/, inst.oprnd [0]/* value*/);
			
			//std::cerr << "noware::mach::cpu::exe::set(\"thread " << inst.thread_id << "\"," << inst.oprnd [1] << "," << inst.oprnd [0] << ")" << std::endl;
			
			// arg 1
			// destination/result
			if (inst.arg_type ["1"])
			{
				std::cerr << "noware::mach::cpu::exe::instr.ref[arg1]==true" << std::endl;
				
				inst.arg ["1"] = get (/*std::string ("thread ") + inst.*/thread_id/* group*/, inst.arg ["1"]);
			}
			else
			{
				std::cerr << "noware::mach::cpu::exe::instr.ref[arg1]==false" << std::endl;
			}
			std::cerr << "noware::mach::cpu::exe::instr[arg1]==[" << inst.arg["1"] << "]" << std::endl;
			
			// arg 2
			if (inst.arg_type ["2"])
			{
				std::cerr << "noware::mach::cpu::exe::instr.ref[arg2]==true" << std::endl;
				
				inst.arg ["2"] = get (/*std::string ("thread ") + inst.*/thread_id/* group*/, inst.arg ["2"]);
			}
			else
			{
				std::cerr << "noware::mach::cpu::exe::instr.ref[arg2]==false" << std::endl;
			}
			std::cerr << "noware::mach::cpu::exe::instr[arg2]==[" << inst.arg["2"] << "]" << std::endl;
			
			// arg 3
			if (inst.arg_type ["3"])
			{
				std::cerr << "noware::mach::cpu::exe::instr.ref[arg3]==true" << std::endl;
				
				inst.arg ["3"] = get (/*std::string ("thread ") + inst.*/thread_id/* group*/, inst.arg ["3"]);
			}
			else
			{
				std::cerr << "noware::mach::cpu::exe::instr.ref[arg3]==false" << std::endl;
			}
			std::cerr << "noware::mach::cpu::exe::instr[arg3]==[" << inst.arg["3"] << "]" << std::endl;
			
			// arg 4
			if (inst.arg_type ["4"])
			{
				std::cerr << "noware::mach::cpu::exe::instr.ref[arg4]==true" << std::endl;
				
				inst.arg ["4"] = get (/*std::string ("thread ") + inst.*/thread_id/* group*/, inst.arg ["4"]);
			}
			else
			{
				std::cerr << "noware::mach::cpu::exe::instr.ref[arg4]==false" << std::endl;
			}
			std::cerr << "noware::mach::cpu::exe::instr[arg4]==[" << inst.arg["4"] << "]" << std::endl;
			
			if (inst.dev == "store")
			{
				if (inst.opr == "set")
				{
					std::cerr << "noware::mach::cpu::exe::instr::store::set" << std::endl;
					//std::cerr << inst.arg ["value"];
					
					//assert (set (thread_id/* group*/, dest/* key*/, src/* value*/));
					result = set (thread_id/* group*/, inst.arg ["2"]/* key*/, inst.arg ["3"]/* value*/);
				}
				else if (inst.opr == "unset")
				{
					std::cerr << "noware::mach::cpu::exe::instr::store::unset" << std::endl;
					//std::cerr << inst.arg ["value"];
					
					result = remove (thread_id/* group*/, inst.arg ["2"]);
				}
				else if (inst.opr == "exist")
				{
					std::cerr << "noware::mach::cpu::exe::instr::store::unset" << std::endl;
					//std::cerr << inst.arg ["value"];
					
					result = exist (thread_id/* group*/, inst.arg ["2"]);
				}
			}
			else if (inst.dev == "cli")
			{
				if (inst.opr == "set")
				{
					std::cerr << "noware::mach::cpu::exe::instr::cli::set[" << inst.arg ["2"] << "]" << std::endl;
					// space
					if (inst.arg ["2"] == "\\_")
					{
						//std::cout << "TWO";
						std::cout << ' ';
					}
					/*
					// back slash
					else if (inst.arg ["2"] == "\\")
					{
						//std::cout << "TWO";
						std::cout << ;
					}
					*/
					// new line
					else if (inst.arg ["2"] == "\\n")
					{
						//std::cout << "TWO";
						std::cout << std::endl;
					}
					else
						std::cout << inst.arg ["2"];
					result = true;
				}
				else if (inst.opr == "get")
				{
					std::cerr << "noware::mach::cpu::exe::instr::cli::get(std::cin," << input << "," << inst.arg ["3"] [0] << ")" << std::endl;
					if (inst.arg ["3"] == "\\n")
						std::getline (std::cin, input, '\n');
					else
						std::getline (std::cin, input, inst.arg ["3"] [0]);
					std::cerr << "noware::mach::cpu::exe::instr::cli::get::set(" << thread_id << "," << inst.arg ["2"] << "," << input << ")" << std::endl;
					result = set (thread_id/* group*/, inst.arg ["2"], input);
					std::cerr << "noware::mach::cpu::exe::instr::cli::get::set()::result==[" << result << "]" << std::endl;
					//result = true;
				}
			}
			
			// if the destination is a reference;
			// if the result is requested to be set
			if (inst.arg ["1"] != "null")
			{
				assert (set (thread_id, inst.arg ["1"], result ? "1" : "0"));
			}
			
			//assert (set (inst.thread_id/* group*/, inst.oprnd [1]/* key*/, inst.oprnd [0]/* value*/));
			
			// remove the instruction from the queue
			// it is now processed
			// it is no longer needed
			//dequeue ();
			
			//// synchronize with our cpu group
			//node.multicast (msg_cpu_serial, grp);
			
			//// synchronize all the members of the thread group
			// tell the caller that we have successfully executed the instruction
			//node.unicast (, inst.thread_id);
			//node.multicast (msg_thread_serial, inst.oprnd [2]);
		//	map_thread ["subject"] = "notification";
		//	map_thread ["success"] = "1";
			//map_thread ["instr.ndx"] = inst.ndx;
			
		//	noware::serialize <std::map <std::string, std::string>> (map_thread_serial, map_thread);
		
		//	std::cerr << "noware::mach::cpu::node.multicast(" << map_thread_serial << "," << inst.thread_id << ")" << std::endl;
		//	std::cerr << "noware::mach::cpu::node.unicast(" << map_thread_serial << "," << inst.thread_id << ")" << std::endl;
			//std::cerr << "noware::mach::cpu::multicast(" << map_thread_serial << "," << inst.thread_id << ")" << std::endl;
			
		//	msg = map_thread_serial;
		//	msg.prepend (zmq::msg::frame ("dummy_request_token"));
			//msg.prepend (zmq::msg::frame (noware::random::string (noware::mach::dev::token_size_dft)));
			
		//	node.multicast (msg, inst.thread_id);
		
			if (inst.arg ["4"] == "0")
			{
				// "0" means "stop";
				// end the execution of the thread
				
				//assert (set (/*std::string ("thread ") + inst.*/thread_id/* group*/, "running"/* key*/, "0"/* value*/));
				assert (clear (thread_id));
			}
			else
			{
				index_max = get (/*std::string ("thread ") + inst.*/thread_id/* group*/, "index.max"/* key*/);
				
				if (inst.arg ["4"] == "next")
				{
					index = get (/*std::string ("thread ") + inst.*/thread_id/* group*/, "index"/* key*/);
					++index;
				}
				else
				{
					index = inst.arg ["4"];
				}
				
				std::cerr << "noware::mach::cpu::exen()::index_max==[" << index_max << "]" << std::endl;
				std::cerr << "noware::mach::cpu::exen()::index==[" << index << "]" << std::endl;
				if (index.operator const unsigned int () > index_max.operator const unsigned int ())
				{
					std::cerr << "noware::mach::cpu::exen()::resetting index=1" << std::endl;
					// assert (set (/*std::string ("thread ") + inst.*/thread_id/* group*/, "running"/* key*/, "0"/* value*/));
					index = 1;
				}
				assert (set (/*std::string ("thread ") + inst.*/thread_id/* group*/, "index"/* key*/, index/* value*/));
				
				inst_next = get (/*std::string ("thread ") + inst.*/thread_id/* group*/, std::string ("instr ") + index.operator const std::string ()/* key*/);
				
				//if (get (/*std::string ("thread ") + inst.*/thread_id/* group*/, "running"/* key*/) == "1")
				//	assert (enqueue (inst_next));
				//else
				//	assert (clear (/*std::string ("thread ") + inst.*/thread_id/* group*/));
				assert (enqueue (inst_next));
				
				//node.unicast (msg, inst.thread_id);
				//multival (msg, inst.thread_id);
				//map_thread.clear ();
			}
		}
		
		std::cerr << "noware::mach::cpu::sleeping..." << std::endl;
		boost::this_thread::sleep_for (boost::chrono::seconds (3));
	}
}

// Store
const bool noware::mach::cpu::exist (const std::string & key) const
{
	return exist (std::string (""), key);
}

const bool noware::mach::cpu::exist (const std::string & group, const std::string & key) const
{
	std::map <std::string, std::string> expression;
	std::string expression_serial;
	
	expression ["subject"] = "existence";
	expression ["group"] = group;
	expression ["key"] = key;
	
	if (!noware::serialize <std::map <std::string, std::string>> (expression_serial, expression))
		return false;
	
	return std::string (anyval (zmq::msg (expression_serial), noware::mach::store::grp_dft)) == "1";
}

const bool noware::mach::cpu::clear (void)
{
	//noware::tree <std::string, std::string> expression;
	std::map <std::string, std::string> expression;
	
	expression ["subject"] = "clearance";
	
	std::string expression_serial;
	if (!noware::serialize <std::map <std::string, std::string>> (expression_serial, expression))
		return false;
	
	//return multival (zmq::msg (expression.serialize ()), noware::mach::store::grp_dft);
	return multival (zmq::msg (expression_serial), noware::mach::store::grp_dft) == "1";
}

const bool noware::mach::cpu::clear (const std::string & group)
{
	//noware::tree <std::string, std::string> expression;
	std::map <std::string, std::string> expression;
	
	expression ["subject"] = "clearance";
	expression ["group"] = group;
	
	std::string expression_serial;
	if (!noware::serialize <std::map <std::string, std::string>> (expression_serial, expression))
		return false;
	
	//return multival (zmq::msg (expression.serialize ()), noware::mach::store::grp_dft);
	return multival (zmq::msg (expression_serial), noware::mach::store::grp_dft) == "1";
}

const bool noware::mach::cpu::remove (const std::string & group, const std::string & key)
{
	std::map <std::string, std::string> expression;
	std::string expression_serial;
	
	expression ["subject"] = "removal";
	expression ["group"] = group;
	expression ["key"] = key;
	
	if (!noware::serialize <std::map <std::string, std::string>> (expression_serial, expression))
		return false;
	
	return std::string (anyval (zmq::msg (expression_serial), noware::mach::store::grp_dft)) == "1";
}

const bool noware::mach::cpu::remove (const std::string & key)
{
	return remove (std::string (""), key);
}

const std::string/* value*/ noware::mach::cpu::get (const std::string & group, const std::string & key) const
{
	std::map <std::string, std::string> expression;
	std::string expression_serial;
	
	expression ["subject"] = "obtainment";
	expression ["group"] = group;
	expression ["key"] = key;
	
	if (!noware::serialize <std::map <std::string, std::string>> (expression_serial, expression))
		return "";
	
	return std::string (anyval (zmq::msg (expression_serial), noware::mach::store::grp_dft));
}

const std::string/* value*/ noware::mach::cpu::get (const std::string & key) const
{
	return get (std::string (""), key);
}

const bool/* success*/ noware::mach::cpu::set (const std::string & group, const std::string & key, const std::string & value)
{
	std::cerr << "noware::mach::cpu::set()::in scope" << std::endl;
	
	std::map <std::string, std::string> expression;
	std::string expression_serial;
	
	expression ["subject"] = "assignment";
	expression ["group"] = group;
	expression ["key"] = key;
	expression ["value"] = value;
	
	if (!noware::serialize <std::map <std::string, std::string>> (expression_serial, expression))
	{
		std::cerr << "noware::mach::cpu::set()::serialize()::false" << std::endl;
		
		return false;
	}
	
	std::cerr << "noware::mach::cpu::set()::return" << std::endl;
	return std::string (anyval (zmq::msg (expression_serial), noware::mach::store::grp_dft)) == "1";
}

const bool/* success*/ noware::mach::cpu::set (const std::string & key, const std::string & value)
{
	return set (std::string (""), key);
}

// Queue
const noware::nr noware::mach::cpu::size (void) const
{
	//bool result;
	std::map <std::string, std::string> expression;
	std::string expression_serial;
	
	expression ["subject"] = "magnitude";
	
	if (!noware::serialize <std::map <std::string, std::string>> (expression_serial, expression))
		return 0;
	
	return std::string (anyval (zmq::msg (expression_serial), noware::mach::queue::grp_dft));
}

const bool noware::mach::cpu::empty (void) const
{
	return size () <= 0;
}

const bool noware::mach::cpu::full (void) const
{
	return false;
}

const noware::mach::cpu::instr noware::mach::cpu::next_dequeue (void)
{
	std::map <std::string, std::string> expression;
	std::string expression_serial;
	instr inst;
	
	expression ["subject"] = "next_dequeue";
	
	if (!noware::serialize <std::map <std::string, std::string>> (expression_serial, expression))
		return inst;
	
	return instr (std::string (anyval (zmq::msg (expression_serial), "noware::mach::queue::nonempty")));
}

const noware::mach::cpu::instr noware::mach::cpu::next (void) const
{
	instr inst;
	
	if (full ())
		return inst;
	
	bool result;
	std::map <std::string, std::string> expression;
	std::string expression_serial;
	
	expression ["subject"] = "next";
	
	if (!noware::serialize <std::map <std::string, std::string>> (expression_serial, expression))
		return inst;
	
	return instr (std::string (anyval (zmq::msg (expression_serial), "noware::mach::queue::nonempty")));
}

const bool noware::mach::cpu::dequeue (void)
{
	if (full ())
		return false;
	
	bool result;
	std::map <std::string, std::string> expression;
	std::string expression_serial;
	
	expression ["subject"] = "dequeue";
	
	if (!noware::serialize <std::map <std::string, std::string>> (expression_serial, expression))
		return false;
	
	return std::string (anyval (zmq::msg (expression_serial), "noware::mach::queue::nonempty")) == "1";
}

const bool noware::mach::cpu::enqueue (const instr & inst)
{
	//return false;
	
	if (full ())
		return false;
	
	//bool result;
	std::map <std::string, std::string> expression;
	std::string expression_serial;
	
	expression ["subject"] = "enqueue";
	expression ["element"] = inst.serialize ();
	
	if (!noware::serialize <std::map <std::string, std::string>> (expression_serial, expression))
		return false;
	
	return std::string (anyval (zmq::msg (expression_serial), "noware::mach::queue::nonfull")) == "1";
}

/*
const bool noware::mach::cpu::enqueue (const std::string & operand1, const opr & op, const std::string & operand2, const std::string & thread_id)
{
	instr inst;
	
	inst.oprn = op;
	inst.oprnd [0] = operand1;
	inst.oprnd [1] = operand2;
	//inst.oprnd [2] = operand3;
	inst.thread_id = thread_id;
	
	return enqueue (inst);
}
*/
/*
const bool noware::mach::cpu::enqueue (const cpu::dev & device, const opr & op, const std::map <std::string, std::string> & arg, const std::string & thread_id)
{
	instr inst;
	
	inst.oprn = op;
	inst.device = device;
	//inst.oprnd [0] = operand1;
	//inst.oprnd [1] = operand2;
	////inst.oprnd [2] = operand3;
	inst.arg = arg;
	inst.thread_id = thread_id;
	
	return enqueue (inst);
}
*/

/*
const bool noware::mach::cpu::respond (const zyre_event_t * event, const std::string & event_type, const zmq::msg & msg_request, zmq::msg & msg_response)
{
	std::cerr << "noware::mach::cpu::respond()::called" << std::endl;
	
	//noware::tree <std::string, std::string> response;
	std::map <std::string, std::string> response;
	//noware::tree <std::string, std::string> message;
	std::map <std::string, std::string> message;
	noware::var result_tmp;
	bool result;
	
//	zframe_t * frm;
	//noware::nr ndx;
	
	//data.clear ();
	//frm = zmsg_first (msg_rx);
//	frm = zmsg_first (zmsg);
	//ndx = 1;
	//while (frm != nullptr)
	//{
		// This makes a copy of the frame.
		//data [ndx] = *frm;
		
		//zframe_destroy (&f);
		
	//	frm = zmsg_next (&other);
	//	++ndx;
	//}
	
	//return other;
	////if (!message.deserialize (msg_rx))
	if (!noware::deserialize <std::map <std::string, std::string>> (message, std::string (msg_request)))
	//if (!noware::deserialize <std::map <std::string, std::string>> (message, std::string ((char *) zframe_data (frm), zframe_size (frm))))
		return false;
	
	result = false;
	
	std::cerr << "noware::mach::cpu::respond()::if::message[subject]==[" << message ["subject"] << ']' << std::endl;
	
	if (message ["type"] == "response")
	{
		std::cerr << "noware::mach::cpu::respond()::if::message[type]==" << message ["type"] << "::in scope" << std::endl;
		
		//if (message ["subject"] == "existence")
		//{
			std::cerr << "noware::mach::cpu::respond()::if::message[subject]==" << message ["subject"] << "::in scope" << std::endl;
			
			//std::cerr << "noware::mach::cpu::receive()::else::msg[subject]==" << msg ["subject"] << "::sleeping" << std::endl;
			//zclock_sleep (1500);
			
			// Redirect the message to the function which asked for it.
			////unicast_local (zmsg_popstr (zmq_msg));
			//result = unicast_local (msg_rx);
			result = unicast_local (msg, "");
			std::cerr << "noware::mach::cpu::respond()::unicast_local(message)==" << (result ? "success" : "failure") << std::endl;
		//}
	}
	
	return result;
}
*/

const bool noware::mach::cpu::load_file (const std::string & file_name)
{
	std::ifstream file;
	std::string thread_id;
	std::string device, operation, arg1, arg2, arg3, arg4;
	bool arg1type, arg2type, arg3type, arg4type;
	//std::string dest, src;
	//bool dest_is_ref, src_is_ref;
	//bool dest_is_offset, src_is_offset;
	cpu::instr _instr;
	//std::map <std::string, std::string> _instr;
	unsigned int _ndx;
	std::string token;
	//std::string token_prev;
	//std::string dest_offset_location, src_offset_location;
	
	file.open (file_name);
	
	if (!file.is_open ())
		return false;
	
	_ndx = 0;
	_instr.thread_id = noware::random::string (16);
	thread_id = std::string ("thread ") + _instr.thread_id;
	//token_prev = "";
	//_instr.thread_id = "1";
	//_instr.oprn = cpu::opr::set;
	//while (file >> operation >> dest >> dest_ref >> dest_is_offset >> dest_offset_location >> src >> src_ref >> src_is_offset >> src_offset_location)
	while (file >> device >> operation >> arg1type >> arg1 >> arg2type >> arg2 >> arg3type >> arg3 >> arg4type >> arg4)
	//while (file >> token)
	{
		++_ndx;
		
		_instr.dev = device;
		_instr.opr = operation;
		
		_instr.arg ["1"] = arg1;
		_instr.arg ["2"] = arg2;
		_instr.arg ["3"] = arg3;
		_instr.arg ["4"] = arg4;
		
		_instr.arg_type ["1"] = arg1type;
		_instr.arg_type ["2"] = arg2type;
		_instr.arg_type ["3"] = arg3type;
		_instr.arg_type ["4"] = arg4type;
		
		assert (set (thread_id, std::string ("instr ") + noware::nr (_ndx).operator const std::string (), _instr.serialize ()));
	}
	
	file.close ();
	
	if (_ndx > 0)
	{
		//assert (set (std::string ("thread ") + _instr.thread_id, "running", "0"));
		assert (set (thread_id, "running", "1"));
		assert (set (thread_id, "index", "1"));
		//set (std::string ("thread ") + _instr.thread_id, "running", "0");
		assert (set (thread_id, "index.max", noware::nr (_ndx).operator const std::string ()));
		
		_instr = get (thread_id, "instr 1");
		assert (enqueue (_instr));
	}
	
	//_loaded = true;
	
	return true;
}

const bool/* success*/ noware::mach::cpu::search (zmq::msg & msg_result, const zmq::msg & msg_resp)
{
	std::cerr << "noware::mach::cpu::search()::called" << std::endl;
	
	//noware::tree <std::string, std::string> resp;
	std::map <std::string, std::string> resp;
	//noware::tree <std::string, std::string> result;
	//std::string result;
	noware::var result_tmp;
	//bool result;
	
	//if (!resp.deserialize (msg_resp))
	if (!noware::deserialize <std::map <std::string, std::string>> (resp, std::string (msg_resp)))
	{
		std::cerr << "noware::mach::cpu::search()::deserialize::failure" << std::endl;
		return false;
	}
	std::cerr << "noware::mach::cpu::search()::deserialize::success" << std::endl;
	
	
	//result ["subject"] = resp ["subject"];
	
	// Store
	if (resp ["subject"] == "existence")
	{
		msg_result = resp ["value"];
		
		return msg_result == "1";
	}
	else if (resp ["subject"] == "obtainment")
	{
		if (resp ["value.exist"] == "0")
		{
			return false;
		}
		
		msg_result = resp ["value"];
		
		return true;
	}
	else if (resp ["subject"] == "assignment")
	{
		msg_result = resp ["value"];
		
		return msg_result == "1";
	}
	else if (resp ["subject"] == "removal")
	{
		msg_result = resp ["value"];
		
		//return msg_result == "1";
		return false;
	}
	else if (resp ["subject"] == "clearance")
	{
		msg_result = resp ["value"];
		
		//return msg_result == "1";
		return false;
	}
	// Queue
	else if (resp ["subject"] == "magnitude")
	{
		std::cerr << "noware::mach::cpu::search()::subject==[" << resp ["subject"] << ']' << std::endl;
		
		result_tmp = msg_result;
		//if (result_tmp.kind () != noware::var::type::nr)
		//	result_tmp = 0;
		
		//result += data.size ();
		//result ["value"] += resp ["value"];
		result_tmp += noware::var (resp ["value"]);
		msg_result = result_tmp;
		
		std::cerr << "noware::mach::cpu::search()::result_tmp==[" << result_tmp << ']' << std::endl;
		std::cerr << "noware::mach::cpu::search()::msg_result==[" << std::string (msg_result) << ']' << std::endl;
		
		return false;
	}
	else if (resp ["subject"] == "next_dequeue")
	{
		std::cerr << "noware::mach::cpu::search()::subject==[" << resp ["subject"] << ']' << std::endl;
		
		//std::cerr << "noware::mach::cpu::search()::queue.front ()==[" << queue.front () << ']' << std::endl;
		
		//result_tmp = queue.front ();
		//std::cerr << "noware::mach::cpu::search()::result_tmp==[" << result_tmp << ']' << std::endl;
		
		
		if (resp ["success"] == "0")
			return false;
		
		//msg_result = result_tmp;
		//msg_result = queue.front ();
		msg_result = resp ["value"];
		std::cerr << "noware::mach::cpu::search()::msg_result==[" << std::string (msg_result) << ']' << std::endl;
		
		return true;
		//return false;
		
		
		//std::cerr << "noware::mach::cpu::search()::resp[success]==[" << resp ["success"] << ']' << std::endl;
		//return resp ["success"] == "1";
	}
	else if (resp ["subject"] == "next")
	{
		std::cerr << "noware::mach::cpu::search()::subject==[" << resp ["subject"] << ']' << std::endl;
		
		//std::cerr << "noware::mach::cpu::search()::queue.front ()==[" << queue.front () << ']' << std::endl;
		
		//result_tmp = queue.front ();
		//std::cerr << "noware::mach::cpu::search()::result_tmp==[" << result_tmp << ']' << std::endl;
		
		
		if (resp ["success"] == "0")
			return false;
		
		//msg_result = result_tmp;
		//msg_result = queue.front ();
		msg_result = resp ["value"];
		std::cerr << "noware::mach::cpu::search()::msg_result==[" << std::string (msg_result) << ']' << std::endl;
		
		return true;
		//return false;
		
		
		//std::cerr << "noware::mach::cpu::search()::resp[success]==[" << resp ["success"] << ']' << std::endl;
		//return resp ["success"] == "1";
	}
	else if (resp ["subject"] == "dequeue")
	{
		std::cerr << "noware::mach::cpu::search()::subject==[" << resp ["subject"] << ']' << std::endl;
		
		/*
		queue.pop ();
		
		if (empty_local ())
		{
			assert (node.leave ("noware::mach::queue::nonempty"));
		}
		
		assert (node.join ("noware::mach::queue::nonfull"));
		
		
		msg_result = "1";
		
		std::cerr << "noware::mach::queue::search()::result_tmp==[" << result_tmp << ']' << std::endl;
		std::cerr << "noware::mach::queue::search()::msg_result==[" << std::string (msg_result) << ']' << std::endl;
		
		return true;
		*/
		
		msg_result = resp ["value"];
		
		return msg_result == "1";
	}
	else if (resp ["subject"] == "enqueue")
	{
		std::cerr << "noware::mach::cpu::search()::subject==[" << resp ["subject"] << ']' << std::endl;
		
		/*
		queue.push (resp ["element"]);
		
		if (full_local ())
		{
			assert (node.leave ("noware::mach::queue::nonfull"));
		}
		
		assert (node.join ("noware::mach::queue::nonempty"));
		
		
		msg_result = "1";
		
		std::cerr << "noware::mach::queue::search()::result_tmp==[" << result_tmp << ']' << std::endl;
		std::cerr << "noware::mach::queue::search()::msg_result==[" << std::string (msg_result) << ']' << std::endl;
		
		return true;
		*/
		
		msg_result = resp ["value"];
		
		return msg_result == "1";
	}
	
	return false;
}
