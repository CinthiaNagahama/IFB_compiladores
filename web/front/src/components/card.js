import React from "react";

export default function Card(props) {
  return (
    <div className='flex flex-col border w-full '>
      <span className='bg-purple-900 flex justify-center text-white text-xl font-medium py-1 px-2'>{props.name}</span>
      <span className='bg-zinc-300 text-zinc-900 p-3 whitespace-pre h-full'>{props.code}</span>
    </div>
  );
}
